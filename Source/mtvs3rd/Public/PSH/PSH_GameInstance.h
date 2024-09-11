// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PSH_HttpDataTable.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PSH_GameInstance.generated.h"

UCLASS()
class MTVS3RD_API UPSH_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPSH_GameInstance();

	virtual void Init() override;

	virtual void OnStart() override;

	void GetOnlineSubsystem();

	UFUNCTION()
	void CreateGameSession();

	UFUNCTION()
	void JoinGameSession();

	void OnJoinSessionComplate(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
	void OnFindSessionComplete(bool bWasSuccessful);

	void OnCreateSessionComplete(FName SessionName , bool bWasSuccessful);

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;

	FOnFindSessionsCompleteDelegate FindSessionCompleteDelegate;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

	IOnlineSessionPtr OnlineSessionInterface;
	
private:
	UPROPERTY()
	FPSH_HttpDataTable PlayerData;

	UPROPERTY()
	FPSH_HttpDataTable ReturnData;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	class UDataTable * DataTable;

	void SetStartData(FPSH_HttpDataTable data);

	FPSH_HttpDataTable GetData(int num);

	void SetdataUpdatae(FPSH_HttpDataTable data);
};
