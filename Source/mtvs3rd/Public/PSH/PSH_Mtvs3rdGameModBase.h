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

protected:
	virtual void BeginPlay() override;

	APSH_Mtvs3rdGameModBase();



	// 플레이어 로그인 시도 할때
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	// 플레이어 로그인 이후
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:

	UPROPERTY()
	class UPSH_GameInstance * Gi;

	// 플레이어 구조체
	FPSH_HttpDataTable PlayerData;

	UPROPERTY()
	class ABS_PlayerState * playerState; // 플레이어 변수 저장 장소
	
	TMap<int,int> ChoiceNum;

	UPROPERTY(EditDefaultsOnly)
	int LastChoiceNum = 0;    // 함수 실행 체크 변수 최대 플레이어 수보다 많도록 체크하는 용도.

	UPROPERTY(EditDefaultsOnly)
	int playerCount = 0;   // 최대 플레이어 수 

	UPROPERTY()
	class APSH_LastChoiceActor * ChoiceActor;

public:
	void SetData(FPSH_HttpDataTable Data);

	void LastChoice(int FromId, int ToId);

	FPSH_HttpDataTable GetData(int num);

	void ChekChoice();

	void SetActor(class APSH_LastChoiceActor * Actor);





	
private:
};
