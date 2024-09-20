// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PSH_HttpDataTable.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "HttpFwd.h"
#include "PSH_GameInstance.generated.h"

UCLASS()
class MTVS3RD_API UPSH_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
/// ���� ���� ����

	virtual void Init() override;

	virtual void OnStart() override;

	void GetOnlineSubsystem();

	UFUNCTION()
	void CreateGameSession();

	UFUNCTION()
	void FindOtherSession();

	/*void JoinSeesion();*/

	void OnJoinSessionComplate(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
	void OnFindSessionComplete(bool bWasSuccessful);

	void OnCreateSessionComplete(FName SessionName , bool bWasSuccessful);

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;

	FOnFindSessionsCompleteDelegate FindSessionCompleteDelegate;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	IOnlineSessionPtr OnlineSessionInterface;

	FName mySessionName = "Couple";
	
// ���� ���� ������ ���
private:
	UPROPERTY()
	FPSH_HttpDataTable PlayerData; // �÷��̾� ������ ����ü.

	UPROPERTY()
	FPSH_HttpDataTable ReturnData;

	UPROPERTY()
	class ABS_PlayerState * playerState;

	int testNum = 0;

	UPROPERTY(EditAnywhere) // ���� ���
	FString URLStart = "http://192.168.0.25:3111/userinfo";
	
	UPROPERTY(EditAnywhere) // ��ư ���� Ŭ������
	FString URLQuest = "http://192.168.0.25:3111/survey";
	UPROPERTY(EditAnywhere) // ������Ʈ ���� ��û
	FString URLState = "http://192.168.0.25:3111/calculate_affinity";
	UPROPERTY(EditAnywhere) // ���� ���� �� 
	FString URLChoose = "http://192.168.0.25:3111/match_status";

	UPROPERTY(EditAnywhere) // ���� ȣ���� ���
	FString URLScore = "http://192.168.0.25:3111/interview_event";
	

public:

	// ���� ���
	void StatDataJson();
    void SetStartData(FPSH_HttpDataTable Data);
	void ReqStartPost(FString json);
    void OnStartResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	
	// ����Ʈ ���� ������ ���
	void QuestButtonJson(int ButtonNum, int QestNum , int playerID);
    void ReqQuestPost(FString json);
    void OnResQuestPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	
	// ������ ������Ʈ ���� ���
	void QuestStateButtonJson();

    UFUNCTION(Server,Reliable)
	void SRPC_QuestStateButtonJson();
    UFUNCTION(NetMulticast,Reliable)
	void MRPC_QuestStateButtonJson();
    void ReqQuestStatePost(FString json);
    void OnResQuestStatePost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	class UDataTable * DataTable;

	FPSH_HttpDataTable GetData(int num);
    FPSH_HttpDataTable GetStartData();

	void SetdataUpdatae(FPSH_HttpDataTable data);


};
