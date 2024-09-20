// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "PSH_HttpDataTable.h"
#include "PSH_Mtvs3rdGameModBase.generated.h"


UCLASS()
class MTVS3RD_API APSH_Mtvs3rdGameModBase : public AGameModeBase
{
	GENERATED_BODY()
	
	APSH_Mtvs3rdGameModBase();

public:

// 	FHttopStartData GetStartData();

	// 플레이어 로그인 시도 할때
	/*virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;*/

	// 플레이어 로그인 이후
	virtual void PostLogin(APlayerController* NewPlayer) override;
	UPROPERTY()
	class UPSH_GameInstance * Gi;

	
	FPSH_HttpDataTable PlayerData;

	UPROPERTY()
	class ABS_PlayerState * playerState;
	
	UPROPERTY(EditDefaultsOnly)
	FName LevelName;

	UPROPERTY()
	float TestScore = 75;

	TArray<int> ChoiceNum;

	int LastChoiceNum = 0;

	UPROPERTY(EditDefaultsOnly)
	int playerCount = 0;

	UPROPERTY()
	class UPSH_LastChoiceWidget * ChoiceWidget;


	void SetData(FPSH_HttpDataTable Data);


	void QestButtonJson(int ButtonNum, int QestNum , int playerID);

	void LastChoice(int FromId, int ToId);

	FPSH_HttpDataTable GetData(int num);

	void ChekChoice();

	void SetLastWdiget(class UPSH_LastChoiceWidget* widget);

	
protected:
	virtual void BeginPlay() override;


	
private:
};
