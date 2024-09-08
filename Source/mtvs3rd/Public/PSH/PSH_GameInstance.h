// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PSH_HttpDataTable.h"
#include "PSH_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UPSH_GameInstance : public UGameInstance
{
	GENERATED_BODY()

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
