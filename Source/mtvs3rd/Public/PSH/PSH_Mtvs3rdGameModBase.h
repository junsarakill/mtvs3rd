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

public:

// 	FHttopStartData GetStartData();

	UPROPERTY()
	class UPSH_GameInstance * Gi;

	void SetStartData(FPSH_HttpDataTable Data);
	FPSH_HttpDataTable PlayerData;

	UPROPERTY(EditDefaultsOnly)

	int32 id = 0;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable * DataTable;

	void ReqPost(FString json, FString URL);

	void SetData(FPSH_HttpDataTable Data);

	void StatDataJson();

	void QestButtonJson(int num);

	// 응답받을 함수
	void OnResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

protected:
	virtual void BeginPlay() override;

private:


	FString URLStart = "http://192.168.0.14:3111/userinfo";
	FString URLScore = "http://192.168.0.14:3111/lovescore";
};
