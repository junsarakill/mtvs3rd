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

	void SetStartData(FPSH_HttpDataTable Data);
	FPSH_HttpDataTable PlayerData;

	UPROPERTY(EditDefaultsOnly)

	int32 id = 0;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable * DataTable;

	void ReqPost(FString json);


	void StatDataJson();

	void QestButtonJson(int num);

	// 응답받을 함수
	void OnResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

private:


	FString URL = "192.168.0.14:3111/userinfo";
};
