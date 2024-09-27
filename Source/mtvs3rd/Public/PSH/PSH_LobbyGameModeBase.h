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

public:
	// 플레이어 로그인 이후
    virtual void PostLogin(APlayerController *NewPlayer) override;


	virtual void BeginPlay()override;

	

	UPROPERTY(EditDefaultsOnly)
	int playerCount = 0;
	
	void Travel();

	UFUNCTION(NetMulticast,Reliable)
	void MRPC_StartFade();
};
