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
	GENERATED_BODY() // ���������ν��Ͻ�1  
public:
/// ���� ���� ����

	virtual void Init() override;

	void GetOnlineSubsystem();

	UFUNCTION()
	void CreateGameSession();

	UFUNCTION()
	void FindOtherSession();


	void OnJoinSessionComplate(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
	void OnFindSessionComplete(bool bWasSuccessful);

	void OnCreateSessionComplete(FName SessionName , bool bWasSuccessful);

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

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

	void SetData();

	UPROPERTY(EditAnywhere)
	FString URL ="https://0094-59-13-225-125.ngrok-free.app";

	UPROPERTY(EditAnywhere) // ���� ���
	FString URLStart = FString::Printf(TEXT("%s/userinfo"),*URL);
	
	UPROPERTY(EditAnywhere) // ��ư ���� Ŭ������
    FString URLQuest = FString::Printf(TEXT("%s/survey"), *URL);

	UPROPERTY(EditAnywhere) // ������Ʈ ���� ��û
    FString URLState = FString::Printf(TEXT("%s/calculate_affinity"), *URL);

	UPROPERTY(EditAnywhere) // ���� ���� �� 
	FString URLChoose = FString::Printf(TEXT("%s/match_status"), *URL);

	UPROPERTY(EditAnywhere) // ���� ȣ���� ���
    FString URLScore = FString::Printf(TEXT("%s/interview_event"), *URL);

	UPROPERTY(EditAnywhere) // ���� ������ �ޱ�  ���
	FString URLStartRequest = FString::Printf(TEXT("%s/get_user_info_by_id_groupid"),*URL);
	

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
	void SRPC_SaveData();

    UFUNCTION(Server,Reliable)
	void SRPC_QuestStateButtonJson();
    UFUNCTION(NetMulticast,Reliable)
	void MRPC_QuestStateButtonJson();
    void ReqQuestStatePost(FString json);

    void OnResQuestStatePost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	// ��Ī ���� ���
	void MatchDataJson();
    void ReqMatchDataJson(FString json);
	void OnResMatchDataJson(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	void LastChoise(int FromId, int ToId);
	
	void StartDataReQestJson();
	void ReqStartDataReQestPost(FString json);
    void OnStartDataReQestResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	class UDataTable * DataTable;

	FPSH_HttpDataTable GetData(int num);
    FPSH_HttpDataTable GetStartData();

	void SetdataUpdatae(FPSH_HttpDataTable data);


};
