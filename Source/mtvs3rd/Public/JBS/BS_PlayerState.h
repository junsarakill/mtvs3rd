// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PSH/PSH_HttpDataTable.h"
#include "BS_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API ABS_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
protected:
	// 플레이어 데이터 구조체
	UPROPERTY(VisibleAnywhere, Category="Default|Values", BlueprintGetter=GetPlayerData, BlueprintSetter=SetPlayerData)
	FPSH_HttpDataTable playerData;

public:
	UFUNCTION(BlueprintGetter)
	FPSH_HttpDataTable GetPlayerData()
	{
		return playerData;
	}
	UFUNCTION(BlueprintSetter)
	void SetPlayerData(FPSH_HttpDataTable data);

};
