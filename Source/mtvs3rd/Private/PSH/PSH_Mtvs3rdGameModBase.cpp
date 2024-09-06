// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "PSH_TsetJsonParseLib.h"
#include "PSH/PSH_HttpDataTable.h"
#include "HttpModule.h"
#include "Kismet/GameplayStatics.h"
#include "JBS/BS_PlayerState.h"
#include "PSH/PSH_GameInstance.h"


APSH_Mtvs3rdGameModBase::APSH_Mtvs3rdGameModBase()
{
	//PlayerStateClass = ABS_PlayerState::StaticClass();
}

void APSH_Mtvs3rdGameModBase::BeginPlay()
{
	Super::BeginPlay();

	Gi = Cast<UPSH_GameInstance>(GetGameInstance());

	auto * pc = GetWorld()->GetFirstPlayerController();
	if (pc)
	{
		playerState = Cast<ABS_PlayerState>(pc->PlayerState);
	}
	
}

void APSH_Mtvs3rdGameModBase::SetData(FPSH_HttpDataTable Data)
{
	PlayerData = Data;
}

//  ���۽� 
void APSH_Mtvs3rdGameModBase::SetStartData(FPSH_HttpDataTable Data)
{
	PlayerData = Data; // ������ ��������
	id++;
	PlayerData.Id = id; // id �Ҵ�
	
	Gi->SetStartData(PlayerData); // ������ ���� �� ����

	if(playerState)
	playerState->SetPlayerData(PlayerData); // �÷��̾� ������ ����
	
	StatDataJson(); // ���� ���
	
	
	// ������ ���̺� �̸����� ���� �Ͽ� �ش� ���� ����
	//TArray<FPSH_HttpDataTable*> FoundData;
	//FPSH_HttpDataTable * FoundData  = DataTable->FindRow<FPSH_HttpDataTable>(RowName, TEXT("Looking up player data"));
	
	//DataTable->GetAllRows(TEXT(""), FoundData);
	
// 	for (int i = 0; i < FoundData.Num(); i++)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Name: %s, Age: %d, Gender: %s, MBTI : %s"),
// 			*FoundData[i]->Name, FoundData[i]->Age, *FoundData[i]->Gender, *FoundData[i]->MBTI);
// 	}

// 	if (FoundData)
// 	{
// 		// �ش� �࿡ ����� ���� �����´�.
// 		UE_LOG(LogTemp, Warning, TEXT("Name: %s, Age: %d, Gender: %s, MBTI : %s"),
// 			*FoundData->Name, FoundData->Age, *FoundData->Gender,*FoundData->MBTI);
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Row not found in DataTable."));
// 	}

}

void APSH_Mtvs3rdGameModBase::StatDataJson()
{
	TMap<FString, FString> StartData; // ���̽��� �� ������
	StartData.Add("ID", FString::FromInt(PlayerData.Id));  // Ű , ����
	StartData.Add("Age", FString::FromInt(PlayerData.Age));
	StartData.Add("Name", PlayerData.Name);
	StartData.Add("Gender", PlayerData.Gender);
	StartData.Add("MBTI", PlayerData.MBTI);
	StartData.Add("blood", PlayerData.Blood);

// 	TMap<FString, FPSH_HttpDataTable> StudentData; // ���̽��� �� ������
// 	StudentData.Add("" , PlayerData);

	FString json = UPSH_TsetJsonParseLib::MakeJson(StartData);
	ReqStartPost(json, URLStart); // ���� ���̽� �����ִ°�
}

void APSH_Mtvs3rdGameModBase::ReqStartPost(FString json, FString URL)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// 	// ��û�� ������ ����
	req->SetURL(URL);
	req->SetVerb(TEXT("Post"));
	req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

	req->SetContentAsString(json); // ����

	//req->SetTimeout(); ���� ���� �ð� ����.
	// ������� �Լ��� ����
	req->OnProcessRequestComplete().BindUObject(this, &APSH_Mtvs3rdGameModBase::OnStartResPost);

	// ������ ��û
	req->ProcessRequest();
}

void APSH_Mtvs3rdGameModBase::OnStartResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// ����
		// actorv controll
		// Json�� �Ľ��ؼ� �ʿ��� ������ �̾Ƽ� ȭ�鿡 ����ϰ�ʹ�.
		UE_LOG(LogTemp, Warning, TEXT("creal"));
		FString result = Response->GetContentAsString();
		UPSH_TsetJsonParseLib::JsonParse(result, PlayerData);

        // �����̸�
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);

		// 
		// httpUi->SetTextLog(result);
	}
	else
	{
		// ����
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}

//  ������ UI ����
void APSH_Mtvs3rdGameModBase::QestButtonJson(int ButtonNum , int QestNum)
{
	TMap<FString, FString> QestData; // ���̽��� �� ������
	//QestData.Add("Answer", FString::FromInt(num));  // Ű , ����
	QestData.Add("AffinityScore_ID1; ", "3");
	QestData.Add("AffinityScore_ID2; ", "4");

	// ���� ��������. id
	// ��ư ������ ��������. button Num
	// ���° ����Ʈ����  Qest Num

	FString json = UPSH_TsetJsonParseLib::MakeJson(QestData);

	ReqPost(json, URLScore); // ���� ���̽� �����ִ°�
}

void APSH_Mtvs3rdGameModBase::ReqPost(FString json, FString URL)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// 	// ��û�� ������ ����
	req->SetURL(URL);
	req->SetVerb(TEXT("Post"));
	req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

	req->SetContentAsString(json); // ����

	//req->SetTimeout(); ���� ���� �ð� ����.
	// ������� �Լ��� ����
	req->OnProcessRequestComplete().BindUObject(this, &APSH_Mtvs3rdGameModBase::OnResPost);

	// ������ ��û
	req->ProcessRequest();
}
void APSH_Mtvs3rdGameModBase::OnResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// ����
		// actorv controll
		// Json�� �Ľ��ؼ� �ʿ��� ������ �̾Ƽ� ȭ�鿡 ����ϰ�ʹ�.
		UE_LOG(LogTemp, Warning, TEXT("creal"));
		FString result = Response->GetContentAsString();
		UPSH_TsetJsonParseLib::JsonParse(result, PlayerData);

		// 
		// httpUi->SetTextLog(result);
	}
	else
	{
		// ����
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}
