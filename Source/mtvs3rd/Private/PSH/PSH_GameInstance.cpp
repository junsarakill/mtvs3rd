// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_GameInstance.h"
#include "PSH/PSH_HttpDataTable.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSessionSettings.h"


UPSH_GameInstance::UPSH_GameInstance() : CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete))
, FindSessionCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionComplete)),
JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplate))
{

}

void UPSH_GameInstance::Init()
{
	Super::Init();
}

void UPSH_GameInstance::OnStart()
{
	Super::OnStart();
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
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Game Session Interface is invailed")));

		return;
	}

	auto ExistingSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr) // 이미 세션이 존재한다면 기존 세션을 삭제한다.
	{
		OnlineSessionInterface->DestroySession(NAME_GameSession);

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Black, FString::Printf(TEXT("Destroy session : %s"), NAME_GameSession));
	}

	//세션 생성 완료 후 호출될 delegate 리스트에 CreateSessionCompleteDelegate 추가
	OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());

	SessionSettings->bIsLANMatch = false;       // Lan 연결이 가능여부
	SessionSettings->NumPublicConnections = 4;  // 최대 접속 가능 수
	SessionSettings->bAllowJoinInProgress = true; // Session 진행중에 접속 허용
	SessionSettings->bAllowJoinViaPresence = true; // 세션 참가 지역을 현재 지역으로 제한  (스팀의 presence 사용)
	SessionSettings->bShouldAdvertise = true;   // 현재 세션을 광고할지 (스팀의 다른 플레이어에게 세션 홍보 여부)
	SessionSettings->bUsesPresence = true;		// 현재 지역에 세션 표시
	SessionSettings->bUseLobbiesIfAvailable = true;	// 플랫폼이 지원하는 경우 로비 API 사용
	SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	/*FOnlineSessionSettings의 Set함수는 SessionSetting할 때 Key와 Value 짝으로 옵션을 세팅해주는 함수다.
위 코드는 세션의 MatchType을 '모두에게 열림(FreeForAll)'으로 설정하고, 온라인 서비스와 핑을 통해 세션을 홍보할 수 있게 설정하는 코드이다.*/

// Local Player를 호스트로 설정하여 하여 세션 생성하기
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
}

void UPSH_GameInstance::JoinGameSession()
{
	if (!OnlineSessionInterface.IsValid()) // 세션 인터페이스 유효성 검사
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Game Session Interface is invailed")));

		return;
	}

	// Find Session Complete Delegate 등록
	OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegate);

	// Find Game Session
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 10000; // 검색 결과로 나오는 세션 수 최대값
	SessionSearch->bIsLanQuery = false; // LAN 사용 여부
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(FName("MatchType"), FString("FreeForAll"), EOnlineComparisonOp::Equals);
	// 찾을 세션 쿼리를 현재로 설정한다

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());

}

void UPSH_GameInstance::OnJoinSessionComplate(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!OnlineSessionInterface.IsValid())
		return;

	// 세션에 조인했다면 IP Address얻어와서 해당 서버에 접속
	FString Address;
	if (OnlineSessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Connect String : %s"), *Address));

		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (PlayerController)
			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}

void UPSH_GameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	if (!OnlineSessionInterface.IsValid() || !bWasSuccessful)
		return;

	for (auto Result : SessionSearch->SearchResults)
	{
		FString Id = Result.GetSessionIdStr();
		FString User = Result.Session.OwningUserName;

		// 매치 타입 확인하기
		FString MatchType;
		Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Session ID : %s / Owner : %s"), *Id, *User));

		// 세션의 매치 타입이 "FreeForAll"일 경우 세션 참가
		if (MatchType == FString("FreeForAll"))
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Joining Match Type : %s"), *MatchType));

			// Join Session Complete Delegate 등록 
			OnlineSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			OnlineSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Result);
		}
	}
}

void UPSH_GameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Created session : %s"), *SessionName.ToString()));

				UWorld* World = GetWorld();
				if (World)
				World->ServerTravel(FString("/Script/Engine.World'/Game/Main/MainMap.MainMap'?listen"));
	}

	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Failed to create session!")));
	}
}

void UPSH_GameInstance::SetStartData(FPSH_HttpDataTable data)
{
	PlayerData = data; // 데이터 저장

	FString num = FString::FromInt(PlayerData.Id);

	// 같은 Name으로 접근하면 덮어 씌워진다.
	FName RowName = FName(num); // 이름 저장 
	DataTable->AddRow(RowName, PlayerData); // 데이터 테이블에 추가.//

	UE_LOG(LogTemp,Warning,TEXT("GameInstance"));
	PlayerData.PrintStruct();
}

FPSH_HttpDataTable UPSH_GameInstance::GetData(int num)
{
	FString numstring = FString::FromInt(num);

	// 같은 Name으로 접근하면 덮어 씌워진다.
	FName RowName = FName(numstring); // 이름 저장 
	FPSH_HttpDataTable* FoundData = DataTable->FindRow<FPSH_HttpDataTable>(RowName, TEXT("Looking up player data"));

	return *FoundData;
}

void UPSH_GameInstance::SetdataUpdatae(FPSH_HttpDataTable data)
{

}
