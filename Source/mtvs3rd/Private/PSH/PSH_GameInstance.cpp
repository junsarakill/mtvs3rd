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
	}

}

void UPSH_GameInstance::CreateGameSession()
{
	if (!OnlineSessionInterface.IsValid())  //OnlineSessionInterface�� ��ȿ���� üũ�Ѵ�.
	{
		return;
	}

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
	if (!OnlineSessionInterface.IsValid()) // ���� �������̽� ��ȿ�� �˻�
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Game Session Interface is invailed")));
		return;
	}

    PRINTLOG(TEXT("FindOtherSession"));
	// Find Game Session
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 40; // �˻� ����� ������ ���� �� �ִ밪
	SessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";  // LAN ��� ����
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(FName("MatchType"), FString("FreeForAll"), EOnlineComparisonOp::Equals);
	SessionSearch->QuerySettings.Set(FName("SESSION_NAME"), mySessionName.ToString(), EOnlineComparisonOp::Equals);
	// ã�� ���� ������ ����� �����Ѵ�
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
			// ��ġ Ÿ�� Ȯ���ϱ�
			FString MatchType;
			Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);

			FString FindSessionName;
			Result.Session.SessionSettings.Get(FName("SESSION_NAME"), FindSessionName);
			
			PRINTLOG(TEXT("FindSessionComplete"));

			// ������ ��ġ Ÿ���� "FreeForAll"�� ��� ���� ����
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

/// ���� ������ ��� �� ���
void UPSH_GameInstance::SetStartData(FPSH_HttpDataTable Data)
{
    PlayerData = Data; // ������ ��������
    const FUniqueNetIdPtr netID =
        GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

    if (netID)
    {
        PlayerData.Id = FCString::Atoi(*netID->ToString()); // Id �Ҵ�
    }
    else
    {
        PlayerData.Id = 0;
    }

    if (GEngine)
       GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT("ID : %d"), PlayerData.Id)); // ������ ���� ID

    StatDataJson(); // ���� ���

    FString num = FString::FromInt(PlayerData.Id); // ID �� Ű ���� 

    // ���� Name���� �����ϸ� ���� ��������.
   
	SRPC_SaveData();
}

void UPSH_GameInstance::StatDataJson()
{
    TMap<FString, FString> StartData;                     // ���̽��� �� ������
    StartData.Add("Id", FString::FromInt(PlayerData.Id)); // Ű , ����
    StartData.Add("GroupID", mySessionName.ToString());
    StartData.Add("Name", PlayerData.Name);
    StartData.Add("Age", FString::FromInt(PlayerData.Age));
    StartData.Add("Gender", PlayerData.Gender);
    StartData.Add("MBTI", PlayerData.MBTI);
    StartData.Add("Blood", PlayerData.Blood);

    // 	TMap<FString, FPSH_HttpDataTable> StudentData; // ���̽��� �� ������
    // 	StudentData.Add("" , PlayerData);

    FString json = UPSH_JsonParseLibrary::MakeJson(StartData);
    ReqStartPost(json); // ���� ���̽� �����ִ°�
}

void UPSH_GameInstance::ReqStartPost(FString json)
{
    FHttpModule &httpModule = FHttpModule::Get();
    TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

    // 	// ��û�� ������ ����
    req->SetURL(URLStart);
    req->SetVerb(TEXT("Post"));
    req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

    req->SetContentAsString(json); // ����

    // req->SetTimeout(); ���� ���� �ð� ����.
    //  ������� �Լ��� ����
    req->OnProcessRequestComplete().BindUObject(this, &UPSH_GameInstance::OnStartResPost);

    // ������ ��û
    req->ProcessRequest();
}

void UPSH_GameInstance::OnStartResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully)
    {
        // ����
        // actorv controll
        // Json�� �Ľ��ؼ� �ʿ��� ������ �̾Ƽ� ȭ�鿡 ����ϰ�ʹ�.
        UE_LOG(LogTemp, Warning, TEXT("creal"));
        FString result = Response->GetContentAsString();
       FString Protocol = UPSH_JsonParseLibrary::ProtocolJson(result); // �������� Ȯ��
        if (Protocol == "Success")
        {
            FindOtherSession();
			// ����
        }
        else
        {
            PRINTLOG(TEXT("ReQuestFailed"));
			// ����
        }
    }
    else
    {
        // ����
        UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
    }
}

void UPSH_GameInstance::QuestButtonJson(int ButtonNum, int QestNum, int playerID) 
{
    TMap<FString, FString> QestData;                      // ���̽��� �� ������
    QestData.Add("ID", FString::FromInt(playerID)); // � �÷��̾
    QestData.Add("GroupID", mySessionName.ToString()); 
    QestData.Add("QestNum", FString::FromInt(QestNum));   // ���° ����Ʈ��
    QestData.Add("Answer", FString::FromInt(ButtonNum));  // ����� ��������

    FString json = UPSH_JsonParseLibrary::MakeJson(QestData);

    ReqQuestPost(json); // ���� ���̽� �����ִ°�
}

void UPSH_GameInstance::ReqQuestPost(FString json)
{
    FHttpModule &httpModule = FHttpModule::Get();
    TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

    // 	// ��û�� ������ ����
    req->SetURL(URLQuest);
    req->SetVerb(TEXT("Post"));
    req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

    req->SetContentAsString(json); // ����

    // req->SetTimeout(); ���� ���� �ð� ����.
    //  ������� �Լ��� ����
    req->OnProcessRequestComplete().BindUObject(this, &UPSH_GameInstance::OnResQuestPost);

    // ������ ��û
    req->ProcessRequest();
}

void UPSH_GameInstance::OnResQuestPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully)
    {

        FString result = Response->GetContentAsString();
        FString Protocol = UPSH_JsonParseLibrary::ProtocolJson(result); // �������� Ȯ��
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
        // ����
        UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
    }
}

void UPSH_GameInstance::QuestStateButtonJson() 
{
	SRPC_QuestStateButtonJson();
}

void UPSH_GameInstance::SRPC_SaveData_Implementation() 
{
    FName RowName = FName(FString::FromInt(PlayerData.Id)); // �̸� ����
    DataTable->AddRow(RowName, PlayerData);                 // ������ ���̺� �߰�.//

    PlayerData.PrintStruct();
}

void UPSH_GameInstance::SRPC_QuestStateButtonJson_Implementation() 
{
	MRPC_QuestStateButtonJson();
}

void UPSH_GameInstance::MRPC_QuestStateButtonJson_Implementation() 
{
    TMap<FString, FString> QestData;                     // ���̽��� �� ������
    QestData.Add("Id", FString::FromInt(PlayerData.Id)); // � �÷��̾
    QestData.Add("GroupID", mySessionName.ToString());   // � �濡

    FString json = UPSH_JsonParseLibrary::MakeJson(QestData);

    ReqQuestPost(json); // ���� ���̽� �����ִ°�
}

void UPSH_GameInstance::ReqQuestStatePost(FString json) 
{
    FHttpModule &httpModule = FHttpModule::Get();
    TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

    // 	// ��û�� ������ ����
    req->SetURL(URLState);
    req->SetVerb(TEXT("Post"));
    req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

    req->SetContentAsString(json); // ����

    // req->SetTimeout(); ���� ���� �ð� ����.
    //  ������� �Լ��� ����
    req->OnProcessRequestComplete().BindUObject(this, &UPSH_GameInstance::OnResQuestPost);

    // ������ ��û
    req->ProcessRequest();
}

void UPSH_GameInstance::OnResQuestStatePost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully) 
    {
        FString result = Response->GetContentAsString();
        UPSH_JsonParseLibrary::JsonParse(result, PlayerData); // ���� ���� ��û
        PlayerData.PrintStruct();

		auto *pc = GetWorld()->GetFirstPlayerController();
        if (pc)
        {
            playerState = Cast<ABS_PlayerState>(pc->PlayerState);
        }
        playerState->SetPlayerData(PlayerData); // �÷��̾� ������ ����
      
    }
    else
    {
        // ����
        UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
    }
}

void UPSH_GameInstance::MatchDataJson() 
{
    TMap<FString, FString> QestData;                     // ���̽��� �� ������
    QestData.Add("Id", FString::FromInt(PlayerData.Id)); // � �÷��̾
    QestData.Add("GroupID", mySessionName.ToString());   // � �濡

    FString json = UPSH_JsonParseLibrary::MakeJson(QestData);

    ReqQuestPost(json); // ���� ���̽� �����ִ°�
}

void UPSH_GameInstance::ReqMatchDataJson(FString json) 
{
    FHttpModule &httpModule = FHttpModule::Get();
    TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

    // 	// ��û�� ������ ����
    req->SetURL(URLChoose);
    req->SetVerb(TEXT("Post"));
    req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

    req->SetContentAsString(json); // ����

    // req->SetTimeout(); ���� ���� �ð� ����.
    //  ������� �Լ��� ����
    req->OnProcessRequestComplete().BindUObject(this, &UPSH_GameInstance::OnResQuestPost);

    // ������ ��û
    req->ProcessRequest();
}

void UPSH_GameInstance::OnResMatchDataJson(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully)
    {
      
    }
    else
    {
        // ����
        UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
    }
}

void UPSH_GameInstance::LastChoise(int FromId, int ToId) 
{   
	
}

void UPSH_GameInstance::StartDataReQestJson() 
{
    TMap<FString, FString> QestData;                     // ���̽��� �� ������
    const FUniqueNetIdPtr netID =
        GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

    QestData.Add("ID", netID->ToString());                         // � �÷��̾
    QestData.Add("GroupID", mySessionName.ToString());   // � �濡

    FString json = UPSH_JsonParseLibrary::MakeJson(QestData);

    ReqStartDataReQestPost(json); // ���� ���̽� �����ִ°�
}

void UPSH_GameInstance::ReqStartDataReQestPost(FString json) 
{
    FHttpModule &httpModule = FHttpModule::Get();
    TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

    // 	// ��û�� ������ ����
    req->SetURL(URLStartRequest);
    req->SetVerb(TEXT("Post"));
    req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

    req->SetContentAsString(json); // ����

    // req->SetTimeout(); ���� ���� �ð� ����.
    //  ������� �Լ��� ����
    req->OnProcessRequestComplete().BindUObject(this, &UPSH_GameInstance::OnStartDataReQestResPost);

    // ������ ��û
    req->ProcessRequest();
}

void UPSH_GameInstance::OnStartDataReQestResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully)
    {
        FString result = Response->GetContentAsString();
        UPSH_JsonParseLibrary::StartJsonParse(result, PlayerData); // ���� ���� ��û
        PlayerData.PrintStruct();
    }
    else
    {
        // ����
        UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
    }
}

FPSH_HttpDataTable UPSH_GameInstance::GetData(int num)
{
	FString numstring = FString::FromInt(num);

	// ���� Name���� �����ϸ� ���� ��������.
	FName RowName = FName(numstring); // �̸� ���� 
	FPSH_HttpDataTable* FoundData = DataTable->FindRow<FPSH_HttpDataTable>(RowName, TEXT("Looking up player data"));

	return *FoundData;
}

FPSH_HttpDataTable UPSH_GameInstance::GetStartData() // �÷��̾� ������Ʈ / �÷��̾� �����Ҷ� ȣ��
{
	return PlayerData;
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
