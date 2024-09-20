// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PSH_LobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API APSH_LobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	// 플레이어 로그인 이후
    virtual void PostLogin(APlayerController *NewPlayer) override;

	UPROPERTY(EditDefaultsOnly)
	int playerCount = 0;
	
};
