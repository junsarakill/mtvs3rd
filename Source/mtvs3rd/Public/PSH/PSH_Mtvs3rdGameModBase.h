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

	UPROPERTY()
	class UPSH_GameInstance * Gi;

	void SetStartData(FPSH_HttpDataTable Data);
	FPSH_HttpDataTable PlayerData;

	UPROPERTY()
	class ABS_PlayerState * playerState;
	
	UPROPERTY(EditDefaultsOnly)
	FName LevelName;

	UPROPERTY(EditDefaultsOnly)

	int32 id = 0;

	TArray<int> ChoiceNum;

	int LastChoiceNum = 0;

	UPROPERTY(EditDefaultsOnly)
	int playerCount = 2;

	UPROPERTY()
	class UPSH_LastChoiceWidget * ChoiceWidget;

	void ReqPost(FString json, FString URL);

	void SetData(FPSH_HttpDataTable Data);


	void QestButtonJson(int ButtonNum, int QestNum);
	void OnResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	void StatDataJson();
	void ReqStartPost(FString json, FString URL);
	// ������� �Լ�
	void OnStartResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	void LastChoice(int FromId, int ToId);

	void ChekChoice();

	void SetLastWdiget(class UPSH_LastChoiceWidget* widget);

protected:
	virtual void BeginPlay() override;

private:


	FString URLStart = "http://192.168.0.19:3111/userinfo";
	FString URLScore = "http://192.168.0.14:3111/lovescore";
};
