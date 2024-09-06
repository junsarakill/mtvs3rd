// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "PSH_TsetJsonParseLib.h"
#include "PSH/PSH_HttpDataTable.h"
#include "HttpModule.h"
#include "Kismet/GameplayStatics.h"



void APSH_Mtvs3rdGameModBase::BeginPlay()
{
	Super::BeginPlay();

	Gi = Cast<UPSH_GameInstance>(GetGameInstance());
}


void APSH_Mtvs3rdGameModBase::SetStartData(FPSH_HttpDataTable Data)
{

	PlayerData = Data;

	id++;
	PlayerData.Id = FString::FromInt(id);
	FName RowName = FName(PlayerData.Id);

	// 같은 Name으로 접근하면 덮어 씌워진다.
	DataTable->AddRow(RowName, PlayerData); // 데이터 테이블에 추가.

	// 플레이어에게 Id 를 줘야한다.


	StatDataJson();

	PlayerData.PrintStruct();
	// 데이터 테이블에 이름으로 접근 하여 해당 행을 저장
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
// 		// 해당 행에 저장된 값을 가져온다.
// 		UE_LOG(LogTemp, Warning, TEXT("Name: %s, Age: %d, Gender: %s, MBTI : %s"),
// 			*FoundData->Name, FoundData->Age, *FoundData->Gender,*FoundData->MBTI);
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Row not found in DataTable."));
// 	}

}

// 버튼 눌러서 초기 대기데이터 설정 해서 

// 버튼 눌러서 한번에 

// 누가 ID, 버튼 번호 < >, 뭐 눌렀는지 < >

// return 

void APSH_Mtvs3rdGameModBase::StatDataJson()
{
	TMap<FString, FString> StartData; // 제이슨에 들어갈 데이터
	StartData.Add("ID", PlayerData.Id);  // 키 , 벨류
	StartData.Add("Age", PlayerData.Age);
	StartData.Add("Name", PlayerData.Name);
	StartData.Add("Gender", PlayerData.Gender);
	StartData.Add("MBTI", PlayerData.MBTI);
	StartData.Add("blood", PlayerData.Blood);


// 	TMap<FString, FPSH_HttpDataTable> StudentData; // 제이슨에 들어갈 데이터
// 	StudentData.Add("" , PlayerData);

	FString json = UPSH_TsetJsonParseLib::MakeJson(StartData);

	ReqPost(json, URLStart); // 만든 제이슨 보내주는거
}

void APSH_Mtvs3rdGameModBase::QestButtonJson(int num)
{
	TMap<FString, FString> QestData; // 제이슨에 들어갈 데이터
	//QestData.Add("Answer", FString::FromInt(num));  // 키 , 벨류
	QestData.Add("AffinityScore_ID1; ", "f1");
	QestData.Add("AffinityScore_ID2; ", "f2");

	FString json = UPSH_TsetJsonParseLib::MakeJson(QestData);

	ReqPost(json, URLScore); // 만든 제이슨 보내주는거
}

void APSH_Mtvs3rdGameModBase::ReqPost(FString json, FString URL)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();
	
	// 	// 요청할 정보를 설정
 		req->SetURL(URL);
	 	req->SetVerb(TEXT("Post"));
	 	req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));
	 
	 	req->SetContentAsString(json); // 내용
	 
	 	//req->SetTimeout(); 세션 유지 시간 설정.
	 	// 응답받을 함수를 연결
	 	req->OnProcessRequestComplete().BindUObject(this, &APSH_Mtvs3rdGameModBase::OnResPost);
	 
	 	// 서버에 요청
	 	req->ProcessRequest();
}

void APSH_Mtvs3rdGameModBase::SetData(FPSH_HttpDataTable Data)
{
	PlayerData = Data;
}

void APSH_Mtvs3rdGameModBase::OnResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 성공
		// actorv controll
		// Json을 파싱해서 필요한 정보만 뽑아서 화면에 출력하고싶다.
		UE_LOG(LogTemp, Warning, TEXT("creal"));
		FString result = Response->GetContentAsString();
		UPSH_TsetJsonParseLib::JsonParse(result, PlayerData);

		UGameplayStatics::OpenLevel(GetWorld(), FName());
		// 
		// httpUi->SetTextLog(result);
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}
