// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_GameInstance.h"
#include "PSH/PSH_HttpDataTable.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSessionSettings.h"
#include "mtvs3rd.h"
#include "Kismet/GameplayStatics.h"
#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "../../../../Plugins/Online/OnlineBase/Source/Public/Online/OnlineSessionNames.h"


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
	// IOnlineSubsystem �޾ƿ���
	IOnlineSubsystem* OnlineSubSystem = IOnlineSubsystem::Get();
	if (OnlineSubSystem)
	{
		// IOnlineSessionPtr �޾ƿ���
		OnlineSessionInterface = OnlineSubSystem->GetSessionInterface();

		OnlineSessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPSH_GameInstance::OnCreateSessionComplete);
		OnlineSessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPSH_GameInstance::OnFindSessionComplete);
		OnlineSessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPSH_GameInstance::OnJoinSessionComplate);
		//IOnlineSessionPtr �̸� ���
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Orange,
				FString::Printf(TEXT("Subsystem �̸� : %s"), *OnlineSubSystem->GetSubsystemName().ToString()
				)
			);
		}
	}

}

void UPSH_GameInstance::CreateGameSession()
{
	if (!OnlineSessionInterface.IsValid())  //OnlineSessionInterface�� ��ȿ���� üũ�Ѵ�.
	{
		return;
	}

// 	auto ExistingSession = OnlineSessionInterface->GetNamedSession(mySessionName);
// 	if (ExistingSession != nullptr) // �̹� ������ �����Ѵٸ� 
// 	{
// 		OnlineSessionInterface->DestroySession(NAME_GameSession); //���� ������ �����Ѵ�.
// 
// 		if (GEngine)
// 			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Black, FString::Printf(TEXT("Destroy session : %s"), NAME_GameSession));
// 	}

	//���� ���� �Ϸ� �� ȣ��� delegate ����Ʈ�� CreateSessionCompleteDelegate �߰�
	//OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsDedicated = false;
	SessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";     

	SessionSettings->NumPublicConnections = 4;  // �ִ� ���� ���� ��
	SessionSettings->bAllowJoinInProgress = true; // Session �����߿� ���� ���
	SessionSettings->bAllowJoinViaPresence = true; // ���� ���� ������ ���� �������� ����  (������ presence ���)
	SessionSettings->bShouldAdvertise = true;   // ���� ������ �������� (������ �ٸ� �÷��̾�� ���� ȫ�� ����)
	SessionSettings->bUsesPresence = true;		// ���� ������ ���� ǥ��
	SessionSettings->bUseLobbiesIfAvailable = true;	// �÷����� �����ϴ� ��� �κ� API ���

	SessionSettings->Set(FName("SESSION_NAME"), mySessionName.ToString() , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	/*FOnlineSessionSettings�� Set�Լ��� SessionSetting�� �� Key�� Value ¦���� �ɼ��� �������ִ� �Լ���.
�� �ڵ�� ������ MatchType�� '��ο��� ����(FreeForAll)'���� �����ϰ�, �¶��� ���񽺿� ���� ���� ������ ȫ���� �� �ְ� �����ϴ� �ڵ��̴�.*/

// Local Player�� ȣ��Ʈ�� �����Ͽ� �Ͽ� ���� �����ϱ�
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
	if (!OnlineSessionInterface.IsValid()) // ���� �������̽� ��ȿ�� �˻�
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Game Session Interface is invailed")));

		return;
	}

	// Find Session Complete Delegate ���
	//OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegate);

	// Find Game Session
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 100; // �˻� ����� ������ ���� �� �ִ밪
	SessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";  // LAN ��� ����
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(FName("MatchType"), FString("FreeForAll"), EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(FName("SESSION_NAME"), mySessionName.ToString(), EOnlineComparisonOp::Equals);
	// ã�� ���� ������ ����� �����Ѵ�

	const FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();
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
			// ��ġ Ÿ�� Ȯ���ϱ�
			FString MatchType;
			Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);

			FString FindSessionName;
			Result.Session.SessionSettings.Get(FName("SESSION_NAME"), FindSessionName);
			
			PRINTLOG(TEXT("FindSessionComplete"));

			// ������ ��ġ Ÿ���� "FreeForAll"�� ��� ���� ����
			if (MatchType == FString("FreeForAll") && FindSessionName == mySessionName)
			{
				const FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

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
	case EOnJoinSessionCompleteResult::Success: // ���ǿ� �����ߴٸ� IP Address���ͼ� �ش� ������ ����

		

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



void UPSH_GameInstance::SetStartData(FPSH_HttpDataTable data)
{
	PlayerData = data; // ������ ����

	FString num = FString::FromInt(PlayerData.Id);

	// ���� Name���� �����ϸ� ���� ��������.
	FName RowName = FName(num); // �̸� ���� 
	DataTable->AddRow(RowName, PlayerData); // ������ ���̺� �߰�.//

	UE_LOG(LogTemp,Warning,TEXT("GameInstance"));
	PlayerData.PrintStruct();
}

FPSH_HttpDataTable UPSH_GameInstance::GetData(int num)
{
	FString numstring = FString::FromInt(num);

	// ���� Name���� �����ϸ� ���� ��������.
	FName RowName = FName(numstring); // �̸� ���� 
	FPSH_HttpDataTable* FoundData = DataTable->FindRow<FPSH_HttpDataTable>(RowName, TEXT("Looking up player data"));

	return *FoundData;
}

void UPSH_GameInstance::SetdataUpdatae(FPSH_HttpDataTable data)
{

	// ������ ���̺� �̸����� ���� �Ͽ� �ش� ���� ����
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
// 		// �ش� �࿡ ����� ���� �����´�.
// 		UE_LOG(LogTemp, Warning, TEXT("Name: %s, Age: %d, Gender: %s, MBTI : %s"),
// 			*FoundData->Name, FoundData->Age, *FoundData->Gender,*FoundData->MBTI);
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Row not found in DataTable."));
// 	}

}
