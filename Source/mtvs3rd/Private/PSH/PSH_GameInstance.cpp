// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_GameInstance.h"
#include "PSH/PSH_HttpDataTable.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSessionSettings.h"
#include "mtvs3rd.h"
#include "Kismet/GameplayStatics.h"
#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "../../../../Plugins/Online/OnlineBase/Source/Public/Online/OnlineSessionNames.h"
#include "HttpModule.h"
#include "JBS/BS_PlayerState.h"
#include "PSH/PSH_JsonParseLibrary.h"


void UPSH_GameInstance::Init()
{
	Super::Init();
	GetOnlineSubsystem();
	 
}

void UPSH_GameInstance::GetOnlineSubsystem()
{
	// IOnlineSubsystem 받아오기
	IOnlineSubsystem* OnlineSubSystem = IOnlineSubsystem::Get();
	if (OnlineSubSystem)
	{
		// IOnlineSessionPtr 받아오기
		OnlineSessionInterface = OnlineSubSystem->GetSessionInterface();

		OnlineSessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPSH_GameInstance::OnCreateSessionComplete);
		OnlineSessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPSH_GameInstance::OnFindSessionComplete);
		OnlineSessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPSH_GameInstance::OnJoinSessionComplate);
		//IOnlineSessionPtr 이름 출력
	}

}

void UPSH_GameInstance::CreateGameSession()
{
	if (!OnlineSessionInterface.IsValid())  //OnlineSessionInterface가 유효한지 체크한다.
	{
		return;
	}

	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsDedicated = false;
	SessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";     

	SessionSettings->NumPublicConnections = 4;  // 최대 접속 가능 수
	SessionSettings->bAllowJoinInProgress = true; // Session 진행중에 접속 허용
	SessionSettings->bAllowJoinViaPresence = true; // 세션 참가 지역을 현재 지역으로 제한  (스팀의 presence 사용)
	SessionSettings->bShouldAdvertise = true;   // 현재 세션을 광고할지 (스팀의 다른 플레이어에게 세션 홍보 여부)
	SessionSettings->bUsesPresence = true;		// 현재 지역에 세션 표시
	SessionSettings->bUseLobbiesIfAvailable = true;	// 플랫폼이 지원하는 경우 로비 API 사용

	SessionSettings->Set(FName("SESSION_NAME"), mySessionName.ToString() , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	/*FOnlineSessionSettings의 Set함수는 SessionSetting할 때 Key와 Value 짝으로 옵션을 세팅해주는 함수다.
위 코드는 세션의 MatchType을 '모두에게 열림(FreeForAll)'으로 설정하고, 온라인 서비스와 핑을 통해 세션을 홍보할 수 있게 설정하는 코드이다.*/

// Local Player를 호스트로 설정하여 하여 세션 생성하기
	const FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

	PRINTLOG(TEXT("netID : %s"), *netID->ToString());
	OnlineSessionInterface->CreateSession(*netID, mySessionName, *SessionSettings);

	PRINTLOG(TEXT("Create Session Start SessionName"));
}

void UPSH_GameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		PRINTLOG(TEXT("OnMyCreateSessionCompelte is Sucess~~~"));
		GetWorld()->ServerTravel(FString("/Game/PSH/Map/WaitRoom?listen"));

	}
	else
	{
		PRINTLOG(TEXT("OnMyCreateSessionCompelte is Failed~~~"));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Failed to create session!")));
	}
}

void UPSH_GameInstance::SetData() {}

void UPSH_GameInstance::FindOtherSession() // FindOtherSession
{
	if (!OnlineSessionInterface.IsValid()) // 세션 인터페이스 유효성 검사
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Game Session Interface is invailed")));
		return;
	}

    PRINTLOG(TEXT("FindOtherSession"));
	// Find Game Session
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 40; // 검색 결과로 나오는 세션 수 최대값
	SessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";  // LAN 사용 여부
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(FName("MatchType"), FString("FreeForAll"), EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(FName("SESSION_NAME"), mySessionName.ToString(), EOnlineComparisonOp::Equals);
	// 찾을 세션 쿼리를 현재로 설정한다
	OnlineSessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UPSH_GameInstance::OnFindSessionComplete(bool bWasSuccessful)
{   
	if (!OnlineSessionInterface.IsValid())
		return;
       
	if (bWasSuccessful)
	{
		for (auto Result : SessionSearch->SearchResults)
		{
			// 매치 타입 확인하기
			FString MatchType;
			Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);

			FString FindSessionName;
			Result.Session.SessionSettings.Get(FName("SESSION_NAME"), FindSessionName);
			
			PRINTLOG(TEXT("FindSessionComplete"));

			// 세션의 매치 타입이 "FreeForAll"일 경우 세션 참가
			if (MatchType == FString("FreeForAll") && FindSessionName == mySessionName)
			{
				PRINTLOG(TEXT("JoinSession"));
				OnlineSessionInterface->JoinSession(0, mySessionName, Result);
				return;
			}
		}
         CreateGameSession();
	}
	else
	{
       
		PRINTLOG(TEXT("FindFailed"));
	}

}

void UPSH_GameInstance::OnJoinSessionComplate(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!OnlineSessionInterface.IsValid())
		return;

	PRINTLOG(TEXT("JoinSessionComplate"));
	auto* pc = GetWorld()->GetFirstPlayerController();
	FString Address;

	switch (Result)
	{
	case EOnJoinSessionCompleteResult::Success: // 세션에 조인했다면 IP Address얻어와서 해당 서버에 접속

		if (pc)
		{
			
			OnlineSessionInterface->GetResolvedConnectString(SessionName, Address);

			if (false == Address.IsEmpty())
			{
				pc->ClientTravel(Address, ETravelType::TRAVEL_Absolute);   
			}
	
		}
		break;
	case EOnJoinSessionCompleteResult::SessionIsFull:
		//PRINTLOG("SessionIsFull");
		break;
	case EOnJoinSessionCompleteResult::SessionDoesNotExist:
		//PRINTLOG("SessionDoesNotExist");
		break;
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
		//PRINTLOG("CouldNotRetrieveAddress");
		break;
	case EOnJoinSessionCompleteResult::AlreadyInSession:
		//PRINTLOG("AlreadyInSession");
		break;
	case EOnJoinSessionCompleteResult::UnknownError:
		//PRINTLOG("UnknownError");
		break;
	default:
		break;
	}
	
}

/// 시작 데이터 등록 과 통신
void UPSH_GameInstance::SetStartData(FPSH_HttpDataTable Data)
{
    PlayerData = Data; // 데이터 가져오기
    const FUniqueNetIdPtr netID =
        GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

    if (netID)
    {
        PlayerData.Id = FCString::Atoi(*netID->ToString()); // Id 할당
    }
    else
    {
        PlayerData.Id = 0;
    }

    if (GEngine)
       GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("ID : %d"), PlayerData.Id)); // 스팀에 고유 ID

    StatDataJson(); // 서버 통신

    FString num = FString::FromInt(PlayerData.Id); // ID 로 키 저장 

    // 같은 Name으로 접근하면 덮어 씌워진다.
   
	SRPC_SaveData();
}

void UPSH_GameInstance::StatDataJson()
{
    TMap<FString, FString> StartData;                     // 제이슨에 들어갈 데이터
    StartData.Add("Id", FString::FromInt(PlayerData.Id)); // 키 , 벨류
    StartData.Add("GroupID", mySessionName.ToString());
    StartData.Add("Name", PlayerData.Name);
    StartData.Add("Age", FString::FromInt(PlayerData.Age));
    StartData.Add("Gender", PlayerData.Gender);
    StartData.Add("MBTI", PlayerData.MBTI);
    StartData.Add("Blood", PlayerData.Blood);

    // 	TMap<FString, FPSH_HttpDataTable> StudentData; // 제이슨에 들어갈 데이터
    // 	StudentData.Add("" , PlayerData);

    FString json = UPSH_JsonParseLibrary::MakeJson(StartData);
    ReqStartPost(json); // 만든 제이슨 보내주는거
}

void UPSH_GameInstance::ReqStartPost(FString json)
{
    FHttpModule &httpModule = FHttpModule::Get();
    TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

    // 	// 요청할 정보를 설정
    req->SetURL(URLStart);
    req->SetVerb(TEXT("Post"));
    req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

    req->SetContentAsString(json); // 내용

    // req->SetTimeout(); 세션 유지 시간 설정.
    //  응답받을 함수를 연결
    req->OnProcessRequestComplete().BindUObject(this, &UPSH_GameInstance::OnStartResPost);

    // 서버에 요청
    req->ProcessRequest();
}

void UPSH_GameInstance::OnStartResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully)
    {
        // 성공
        // actorv controll
        // Json을 파싱해서 필요한 정보만 뽑아서 화면에 출력하고싶다.
        UE_LOG(LogTemp, Warning, TEXT("creal"));
        FString result = Response->GetContentAsString();
       FString Protocol = UPSH_JsonParseLibrary::ProtocolJson(result); // 성공실패 확인
        if (Protocol == "Success")
        {
            FindOtherSession();
			// 성공
        }
        else
        {
            PRINTLOG(TEXT("ReQuestFailed"));
			// 실패
        }
    }
    else
    {
        // 실패
        UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
    }
}

void UPSH_GameInstance::QuestButtonJson(int ButtonNum, int QestNum, int playerID) 
{
    TMap<FString, FString> QestData;                      // 제이슨에 들어갈 데이터
    QestData.Add("ID", FString::FromInt(playerID)); // 어떤 플레이어가
    QestData.Add("GroupID", mySessionName.ToString()); 
    QestData.Add("QestNum", FString::FromInt(QestNum));   // 몇번째 퀘스트에
    QestData.Add("Answer", FString::FromInt(ButtonNum));  // 몇번을 눌렀는지

    FString json = UPSH_JsonParseLibrary::MakeJson(QestData);

    ReqQuestPost(json); // 만든 제이슨 보내주는거
}

void UPSH_GameInstance::ReqQuestPost(FString json)
{
    FHttpModule &httpModule = FHttpModule::Get();
    TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

    // 	// 요청할 정보를 설정
    req->SetURL(URLQuest);
    req->SetVerb(TEXT("Post"));
    req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

    req->SetContentAsString(json); // 내용

    // req->SetTimeout(); 세션 유지 시간 설정.
    //  응답받을 함수를 연결
    req->OnProcessRequestComplete().BindUObject(this, &UPSH_GameInstance::OnResQuestPost);

    // 서버에 요청
    req->ProcessRequest();
}

void UPSH_GameInstance::OnResQuestPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully)
    {

        FString result = Response->GetContentAsString();
        FString Protocol = UPSH_JsonParseLibrary::ProtocolJson(result); // 성공실패 확인
        if (Protocol == "Success")
        {
            QuestStateButtonJson();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed"));
        }
		
    }
    else
    {
        // 실패
        UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
    }
}

void UPSH_GameInstance::QuestStateButtonJson() 
{
	SRPC_QuestStateButtonJson();
}

void UPSH_GameInstance::SRPC_SaveData_Implementation() 
{
    FName RowName = FName(FString::FromInt(PlayerData.Id)); // 이름 저장
    DataTable->AddRow(RowName, PlayerData);                 // 데이터 테이블에 추가.//

    PlayerData.PrintStruct();
}

void UPSH_GameInstance::SRPC_QuestStateButtonJson_Implementation() 
{
	MRPC_QuestStateButtonJson();
}

void UPSH_GameInstance::MRPC_QuestStateButtonJson_Implementation() 
{
    TMap<FString, FString> QestData;                     // 제이슨에 들어갈 데이터
    QestData.Add("Id", FString::FromInt(PlayerData.Id)); // 어떤 플레이어가
    QestData.Add("GroupID", mySessionName.ToString());   // 어떤 방에

    FString json = UPSH_JsonParseLibrary::MakeJson(QestData);

    ReqQuestPost(json); // 만든 제이슨 보내주는거
}

void UPSH_GameInstance::ReqQuestStatePost(FString json) 
{
    FHttpModule &httpModule = FHttpModule::Get();
    TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

    // 	// 요청할 정보를 설정
    req->SetURL(URLState);
    req->SetVerb(TEXT("Post"));
    req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

    req->SetContentAsString(json); // 내용

    // req->SetTimeout(); 세션 유지 시간 설정.
    //  응답받을 함수를 연결
    req->OnProcessRequestComplete().BindUObject(this, &UPSH_GameInstance::OnResQuestPost);

    // 서버에 요청
    req->ProcessRequest();
}

void UPSH_GameInstance::OnResQuestStatePost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully) 
    {
        FString result = Response->GetContentAsString();
        UPSH_JsonParseLibrary::JsonParse(result, PlayerData); // 점수 갱신 요청
        PlayerData.PrintStruct();

		auto *pc = GetWorld()->GetFirstPlayerController();
        if (pc)
        {
            playerState = Cast<ABS_PlayerState>(pc->PlayerState);
        }
        playerState->SetPlayerData(PlayerData); // 플레이어 데이터 저장
      
    }
    else
    {
        // 실패
        UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
    }
}

void UPSH_GameInstance::MatchDataJson() 
{
    TMap<FString, FString> QestData;                     // 제이슨에 들어갈 데이터
    QestData.Add("Id", FString::FromInt(PlayerData.Id)); // 어떤 플레이어가
    QestData.Add("GroupID", mySessionName.ToString());   // 어떤 방에

    FString json = UPSH_JsonParseLibrary::MakeJson(QestData);

    ReqQuestPost(json); // 만든 제이슨 보내주는거
}

void UPSH_GameInstance::ReqMatchDataJson(FString json) 
{
    FHttpModule &httpModule = FHttpModule::Get();
    TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

    // 	// 요청할 정보를 설정
    req->SetURL(URLChoose);
    req->SetVerb(TEXT("Post"));
    req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

    req->SetContentAsString(json); // 내용

    // req->SetTimeout(); 세션 유지 시간 설정.
    //  응답받을 함수를 연결
    req->OnProcessRequestComplete().BindUObject(this, &UPSH_GameInstance::OnResQuestPost);

    // 서버에 요청
    req->ProcessRequest();
}

void UPSH_GameInstance::OnResMatchDataJson(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully)
    {
      
    }
    else
    {
        // 실패
        UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
    }
}

void UPSH_GameInstance::LastChoise(int FromId, int ToId) 
{   
	
}

void UPSH_GameInstance::StartDataReQestJson() 
{
    TMap<FString, FString> QestData;                     // 제이슨에 들어갈 데이터
    const FUniqueNetIdPtr netID =
        GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

    QestData.Add("ID", netID->ToString());                         // 어떤 플레이어가
    QestData.Add("GroupID", mySessionName.ToString());   // 어떤 방에

    FString json = UPSH_JsonParseLibrary::MakeJson(QestData);

    ReqStartDataReQestPost(json); // 만든 제이슨 보내주는거
}

void UPSH_GameInstance::ReqStartDataReQestPost(FString json) 
{
    FHttpModule &httpModule = FHttpModule::Get();
    TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

    // 	// 요청할 정보를 설정
    req->SetURL(URLStartRequest);
    req->SetVerb(TEXT("Post"));
    req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

    req->SetContentAsString(json); // 내용

    // req->SetTimeout(); 세션 유지 시간 설정.
    //  응답받을 함수를 연결
    req->OnProcessRequestComplete().BindUObject(this, &UPSH_GameInstance::OnStartDataReQestResPost);

    // 서버에 요청
    req->ProcessRequest();
}

void UPSH_GameInstance::OnStartDataReQestResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully)
    {
        FString result = Response->GetContentAsString();
        UPSH_JsonParseLibrary::StartJsonParse(result, PlayerData); // 점수 갱신 요청
        PlayerData.PrintStruct();
    }
    else
    {
        // 실패
        UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
    }
}

FPSH_HttpDataTable UPSH_GameInstance::GetData(int num)
{
	FString numstring = FString::FromInt(num);

	// 같은 Name으로 접근하면 덮어 씌워진다.
	FName RowName = FName(numstring); // 이름 저장 
	FPSH_HttpDataTable* FoundData = DataTable->FindRow<FPSH_HttpDataTable>(RowName, TEXT("Looking up player data"));

	return *FoundData;
}

FPSH_HttpDataTable UPSH_GameInstance::GetStartData() // 플레이어 스테이트 / 플레이어 시작할때 호출
{
	return PlayerData;
}

void UPSH_GameInstance::SetdataUpdatae(FPSH_HttpDataTable data)
{

	// 데이터 테이블에 이름으로 접근 하여 해당 행을 저장
	//FPSH_HttpDataTable * FoundData  = DataTable->FindRow<FPSH_HttpDataTable>(RowName, TEXT("Looking up player data"));

	//TArray<FPSH_HttpDataTable*> FoundData;
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
