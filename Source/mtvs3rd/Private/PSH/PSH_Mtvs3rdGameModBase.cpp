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
	
	ChoiceNum.Init(0, 5); // 플레이어 수만큼 만들기로 변경.
	
}

void APSH_Mtvs3rdGameModBase::SetData(FPSH_HttpDataTable Data)
{
	PlayerData = Data;
}

//  시작시 
void APSH_Mtvs3rdGameModBase::SetStartData(FPSH_HttpDataTable Data)
{
	PlayerData = Data; // 데이터 가져오기
	id++;
	PlayerData.Id = id; // id 할당
	
	Gi->SetStartData(PlayerData); // 데이터 갱신 및 저장

	if(playerState)
	playerState->SetPlayerData(PlayerData); // 플레이어 데이터 저장
	
	StatDataJson(); // 서버 통신
	
	
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

void APSH_Mtvs3rdGameModBase::StatDataJson()
{
	TMap<FString, FString> StartData; // 제이슨에 들어갈 데이터
	StartData.Add("ID", FString::FromInt(PlayerData.Id));  // 키 , 벨류
	StartData.Add("Age", FString::FromInt(PlayerData.Age));
	StartData.Add("Name", PlayerData.Name);
	StartData.Add("Gender", PlayerData.Gender);
	StartData.Add("MBTI", PlayerData.MBTI);
	StartData.Add("blood", PlayerData.Blood);

// 	TMap<FString, FPSH_HttpDataTable> StudentData; // 제이슨에 들어갈 데이터
// 	StudentData.Add("" , PlayerData);

	FString json = UPSH_TsetJsonParseLib::MakeJson(StartData);
	ReqStartPost(json, URLStart); // 만든 제이슨 보내주는거
}

void APSH_Mtvs3rdGameModBase::ReqStartPost(FString json, FString URL)
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
	req->OnProcessRequestComplete().BindUObject(this, &APSH_Mtvs3rdGameModBase::OnStartResPost);

	// 서버에 요청
	req->ProcessRequest();
}

void APSH_Mtvs3rdGameModBase::OnStartResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 성공
		// actorv controll
		// Json을 파싱해서 필요한 정보만 뽑아서 화면에 출력하고싶다.
		UE_LOG(LogTemp, Warning, TEXT("creal"));
		FString result = Response->GetContentAsString();
		UPSH_TsetJsonParseLib::JsonParse(result, PlayerData);

        // 시작이름
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);

		// 
		// httpUi->SetTextLog(result);
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}

void APSH_Mtvs3rdGameModBase::LastChoice(int FromId, int ToId) // 4번 불린다. 갱신 가능.
{

	// 시연 용 ( 프로토)
	//ChoiceWidget->
	

	// 최종 선택 판별

	// 각 id 를 저장
	//ChoiceWidget->SetData(PlayerData);
	
	
	ChoiceNum[FromId] = ToId; // 사전에 플레이어의 수만큼 만들어놓은 배열에 상대의 ID 를 집어 넣음

	LastChoiceNum++; // 함수 실행 횟수 체크

	if (LastChoiceNum < playerCount || ChoiceWidget == nullptr) // 테스트 현재 플레이어 수 현재 2
	{
		return;
	}

	ChekChoice();
	

	// 1, 2 남자
	

	// 3. 4 여자
	
	// for문을 돌리면서 Toid
	// 미리 만들어 놓고 비교
	// 각 id 를 비교
	
	// 같으면 성공 UI
	

	// 틀리면 실패 UI
	//

}

void APSH_Mtvs3rdGameModBase::ChekChoice() // 현재는 2명으로 구현되어 있음 4명일 때 UI 어떻게 보여줘야 하는지 잘 모르겠어서 추후 수정
{
	if (ChoiceWidget)
	{
		for (int i = 1; i < 3; i++)  // 전체 확인을 했기 때문에 3명을 검사 할 필요가 없다.
		{
			
			if (ChoiceNum[i] == 0) // 플레이어를 선택 안했거나 플레이어가 아님
			{
				continue;
			}
			else
			{
				if (ChoiceNum[i] == ChoiceNum[ChoiceNum[i]]) // 남자 1번과 누군가 자신을 선택했는지
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

//  시작중 UI 적용
void APSH_Mtvs3rdGameModBase::QestButtonJson(int ButtonNum , int QestNum)
{
	TMap<FString, FString> QestData; // 제이슨에 들어갈 데이터
	//QestData.Add("Answer", FString::FromInt(num));  // 키 , 벨류
	QestData.Add("AffinityScore_ID1; ", "3");
	QestData.Add("AffinityScore_ID2; ", "4");

	// 내가 누구인지. id
	// 버튼 무엇을 눌렀는지. button Num
	// 몇번째 퀘스트인지  Qest Num

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

		Gi->SetStartData(PlayerData);
		playerState->SetPlayerData(PlayerData); // 플레이어 데이터 저장
		// 
		// httpUi->SetTextLog(result);
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}
