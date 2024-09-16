// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "PSH_TsetJsonParseLib.h"
#include "PSH/PSH_HttpDataTable.h"
#include "HttpModule.h"
#include "Kismet/GameplayStatics.h"
#include "JBS/BS_PlayerState.h"
#include "PSH/PSH_GameInstance.h"
#include "PSH/PSH_LastChoiceWidget.h"


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
	
	ChoiceNum.Init(0, 5); // �÷��̾� ����ŭ ������ ����.
	
}

void APSH_Mtvs3rdGameModBase::SetData(FPSH_HttpDataTable Data)
{
	PlayerData = Data;
}

void APSH_Mtvs3rdGameModBase::LastChoice(int FromId, int ToId) // 4�� �Ҹ���. ���� ����. // ���� , ������
{

	// �ÿ� �� ( ������)
	//ChoiceWidget->
	

	// ���� ���� �Ǻ�

	// �� id �� ����
	//ChoiceWidget->SetData(PlayerData);
	
	
	ChoiceNum[FromId] = ToId; // ������ �÷��̾��� ����ŭ �������� �迭�� ����� ID �� ���� ����

	LastChoiceNum++; // �Լ� ���� Ƚ�� üũ

	if (LastChoiceNum < playerCount || ChoiceWidget == nullptr) // �׽�Ʈ ���� �÷��̾� �� ���� 2
	{
		return;
	}

	ChekChoice();
	

	// 1, 2 ����
	

	// 3. 4 ����
	
	// for���� �����鼭 Toid
	// �̸� ����� ���� ��
	// �� id �� ��
	
	// ������ ���� UI
	

	// Ʋ���� ���� UI
	//

}

FPSH_HttpDataTable APSH_Mtvs3rdGameModBase::GetData(int num)
{
	return Gi->GetData(num);
}

void APSH_Mtvs3rdGameModBase::ChekChoice() // ����� 2������ �����Ǿ� ���� 4���� �� UI ��� ������� �ϴ��� �� �𸣰ھ ���� ����
{
	if (ChoiceWidget)
	{
		for (int i = 1; i < 3; i++)  // ��ü Ȯ���� �߱� ������ 3���� �˻� �� �ʿ䰡 ����.
		{
			
			if (ChoiceNum[i] == 0) // �÷��̾ ���� ���߰ų� �÷��̾ �ƴ�
			{
				continue;
			}
			else
			{		// �÷��̾� ��ȣ = 3 / 1
					// 1 2 3 4  /1     arr[1]
				if ( i == ChoiceNum[ChoiceNum[i]]) // ���� 1���� ������ �ڽ��� �����ߴ���
				{
					ChoiceWidget->SuccessChoice();
				}
				else
				{
					ChoiceWidget->FailChoice();
				}
			}
		}
	}
}

void APSH_Mtvs3rdGameModBase::SetLastWdiget(class UPSH_LastChoiceWidget* widget)
{
	ChoiceWidget = widget;
}

//  ������ UI ����
void APSH_Mtvs3rdGameModBase::QestButtonJson(int ButtonNum , int QestNum, int playerID)
{
	TMap<FString, FString> QestData; // ���̽��� �� ������
	QestData.Add("playerID", FString::FromInt(playerID)); // � �÷��̾
	QestData.Add("QestNum", FString::FromInt(QestNum)); // ���° ����Ʈ��
	QestData.Add("Answer", FString::FromInt(ButtonNum)); // ����� ��������
	
	// ���� ��������. id
	// ��ư ������ ��������. button Num
	// ���° ����Ʈ����  Qest Num
	TestScore += 5;
	PlayerData.otherUserID1 = 3;
	PlayerData.syncPercentID1 = TestScore;

	Gi->SetStartData(PlayerData);
	playerState->SetPlayerData(PlayerData); // �÷��̾� ������ ����
	FString json = UPSH_TsetJsonParseLib::MakeJson(QestData);

//	ReqPost(json, URLScore); // ���� ���̽� �����ִ°�
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

		Gi->SetStartData(PlayerData);
		playerState->SetPlayerData(PlayerData); // �÷��̾� ������ ����
		// 
		// httpUi->SetTextLog(result);
	}
	else
	{
		// ����
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}
