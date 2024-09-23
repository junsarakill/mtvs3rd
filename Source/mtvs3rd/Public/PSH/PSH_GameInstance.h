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
	GENERATED_BODY() // 서버게임인스턴스1  
public:
/// 게임 섹션 열기

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
	
// 게임 시작 데이터 통신
private:
	UPROPERTY()
	FPSH_HttpDataTable PlayerData; // 플레이어 데이터 구조체.

	UPROPERTY()
	FPSH_HttpDataTable ReturnData;

	UPROPERTY()
	class ABS_PlayerState * playerState;

	int testNum = 0;

	void SetData();

	UPROPERTY(EditAnywhere)
	FString URL ="https://0094-59-13-225-125.ngrok-free.app";

	UPROPERTY(EditAnywhere) // 최초 통신
	FString URLStart = FString::Printf(TEXT("%s/userinfo"),*URL);
	
	UPROPERTY(EditAnywhere) // 버튼 전부 클릭했음
    FString URLQuest = FString::Printf(TEXT("%s/survey"), *URL);

	UPROPERTY(EditAnywhere) // 스테이트 갱신 요청
    FString URLState = FString::Printf(TEXT("%s/calculate_affinity"), *URL);

	UPROPERTY(EditAnywhere) // 최종 선택 후 
	FString URLChoose = FString::Printf(TEXT("%s/match_status"), *URL);

	UPROPERTY(EditAnywhere) // 직접 호감도 통신
    FString URLScore = FString::Printf(TEXT("%s/interview_event"), *URL);

	UPROPERTY(EditAnywhere) // 시작 데이터 받기  통신
	FString URLStartRequest = FString::Printf(TEXT("%s/get_user_info_by_id_groupid"),*URL);
	

public:

	// 최초 통신
	void StatDataJson();
    void SetStartData(FPSH_HttpDataTable Data);
	void ReqStartPost(FString json);
    void OnStartResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	
	// 퀘스트 설문 데이터 통신
	void QuestButtonJson(int ButtonNum, int QestNum , int playerID);
    void ReqQuestPost(FString json);
    void OnResQuestPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	
	// 데이터 스테이트 갱신 통신
	void QuestStateButtonJson();

    UFUNCTION(Server,Reliable)
	void SRPC_SaveData();

    UFUNCTION(Server,Reliable)
	void SRPC_QuestStateButtonJson();
    UFUNCTION(NetMulticast,Reliable)
	void MRPC_QuestStateButtonJson();
    void ReqQuestStatePost(FString json);

    void OnResQuestStatePost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	// 매칭 성공 통신
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
