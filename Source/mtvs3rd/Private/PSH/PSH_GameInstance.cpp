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
#include "PSH_TsetJsonParseLib.h"
#include "JBS/BS_PlayerState.h"


void UPSH_GameInstance::Init()
{
	Super::Init();
	GetOnlineSubsystem();
	 
}

void UPSH_GameInstance::OnStart()
{
	Super::OnStart();
	
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
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Orange,
				FString::Printf(TEXT("Subsystem 이름 : %s"), *OnlineSubSystem->GetSubsystemName().ToString()
				)
			);
		}
	}

}

void UPSH_GameInstance::CreateGameSession()
{
	if (!OnlineSessionInterface.IsValid())  //OnlineSessionInterface가 유효한지 체크한다.
	{
		return;
	}

// 	auto ExistingSession = OnlineSessionInterface->GetNamedSession(mySessionName);
// 	if (ExistingSession != nullptr) // 이미 세션이 존재한다면 
// 	{
// 		OnlineSessionInterface->DestroySession(NAME_GameSession); //기존 세션을 삭제한다.
// 
// 		if (GEngine)
// 			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Black, FString::Printf(TEXT("Destroy session : %s"), NAME_GameSession));
// 	}

	//세션 생성 완료 후 호출될 delegate 리스트에 CreateSessionCompleteDelegate 추가
	//OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

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
	//const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	const FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

	PRINTLOG(TEXT("netID : %s"), *netID->ToString());
	OnlineSessionInterface->CreateSession(0, mySessionName, *SessionSettings);

	PRINTLOG(TEXT("Create Session Start SessionName"));
}

void UPSH_GameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		PRINTLOG(TEXT("OnMyCreateSessionCompelte is Sucess~~~"));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Created session : %s"), *SessionName.ToString()));

		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(FString("/Game/Main/MainMap?listen"));
                
		}
		
	}
	else
	{
		PRINTLOG(TEXT("OnMyCreateSessionCompelte is Failed~~~"));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Failed to create session!")));
	}
}

void UPSH_GameInstance::FindOtherSession() // FindOtherSession
{
	if (!OnlineSessionInterface.IsValid()) // 세션 인터페이스 유효성 검사
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Game Session Interface is invailed")));

		return;
	}

	// Find Session Complete Delegate 등록
	//OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegate);

	// Find Game Session
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 100; // 검색 결과로 나오는 세션 수 최대값
	SessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";  // LAN 사용 여부
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(FName("MatchType"), FString("FreeForAll"), EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(FName("SESSION_NAME"), mySessionName.ToString(), EOnlineComparisonOp::Equals);
	// 찾을 세션 쿼리를 현재로 설정한다

        const FUniqueNetIdPtr netID =
            GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();
	OnlineSessionInterface->FindSessions(*netID, SessionSearch.ToSharedRef());

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
			}
		}
	}
	else
	{
		PRINTLOG(TEXT("FindFailed"));
	}

}
// void UPSH_GameInstance::JoinSeesion()
// {
// 
// }

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
   
   PlayerData.Id = FCString::Atoi(*netID->ToString()); // Id 할당

    if (GEngine)
       GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("ID : %d"), PlayerData.Id)); // 스팀에 고유 ID

    StatDataJson(); // 서버 통신

    FString num = FString::FromInt(PlayerData.Id); // ID 로 키 저장 

    // 같은 Name으로 접근하면 덮어 씌워진다.
    FName RowName = FName(num);             // 이름 저장
    DataTable->AddRow(RowName, PlayerData); // 데이터 테이블에 추가.//

    PlayerData.PrintStruct();
}

void UPSH_GameInstance::StatDataJson()
{
    TMap<FString, FString> StartData;                     // 제이슨에 들어갈 데이터
    StartData.Add("ID", FString::FromInt(PlayerData.Id)); // 키 , 벨류
    StartData.Add("Age", FString::FromInt(PlayerData.Age));
    StartData.Add("Name", PlayerData.Name);
    StartData.Add("Gender", PlayerData.Gender);
    StartData.Add("MBTI", PlayerData.MBTI);
    StartData.Add("blood", PlayerData.Blood);

    // 	TMap<FString, FPSH_HttpDataTable> StudentData; // 제이슨에 들어갈 데이터
    // 	StudentData.Add("" , PlayerData);

    FString json = UPSH_TsetJsonParseLib::MakeJson(StartData);
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

void UPSH_GameInstance::OnStartResPost(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                             bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully)
    {
        // 성공
        // actorv controll
        // Json을 파싱해서 필요한 정보만 뽑아서 화면에 출력하고싶다.
        UE_LOG(LogTemp, Warning, TEXT("creal"));
        FString result = Response->GetContentAsString();
       FString Protocol = UPSH_TsetJsonParseLib::ProtocolJson(result); // 성공실패 확인
        if (Protocol == "Success")
        {
			// 성공
        }
        else
        {
			// 실패
        }
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
