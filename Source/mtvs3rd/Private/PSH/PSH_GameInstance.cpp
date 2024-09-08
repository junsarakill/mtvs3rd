// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_GameInstance.h"
#include "PSH/PSH_HttpDataTable.h"

void UPSH_GameInstance::SetStartData(FPSH_HttpDataTable data)
{
	PlayerData = data; // 데이터 저장

	FString num = FString::FromInt(PlayerData.Id);

	// 같은 Name으로 접근하면 덮어 씌워진다.
	FName RowName = FName(num); // 이름 저장 
	DataTable->AddRow(RowName, PlayerData); // 데이터 테이블에 추가.//

	UE_LOG(LogTemp,Warning,TEXT("GameInstance"));
	PlayerData.PrintStruct();
}

FPSH_HttpDataTable UPSH_GameInstance::GetData(int num)
{
	FString numstring = FString::FromInt(num);

	// 같은 Name으로 접근하면 덮어 씌워진다.
	FName RowName = FName(numstring); // 이름 저장 
	FPSH_HttpDataTable* FoundData = DataTable->FindRow<FPSH_HttpDataTable>(RowName, TEXT("Looking up player data"));

	return *FoundData;
}

void UPSH_GameInstance::SetdataUpdatae(FPSH_HttpDataTable data)
{

}
