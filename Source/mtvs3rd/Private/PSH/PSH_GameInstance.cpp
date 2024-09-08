// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_GameInstance.h"
#include "PSH/PSH_HttpDataTable.h"

void UPSH_GameInstance::SetStartData(FPSH_HttpDataTable data)
{
	PlayerData = data; // ������ ����

	FString num = FString::FromInt(PlayerData.Id);

	// ���� Name���� �����ϸ� ���� ��������.
	FName RowName = FName(num); // �̸� ���� 
	DataTable->AddRow(RowName, PlayerData); // ������ ���̺� �߰�.//

	UE_LOG(LogTemp,Warning,TEXT("GameInstance"));
	PlayerData.PrintStruct();
}

FPSH_HttpDataTable UPSH_GameInstance::GetData(int num)
{
	FString numstring = FString::FromInt(num);

	// ���� Name���� �����ϸ� ���� ��������.
	FName RowName = FName(numstring); // �̸� ���� 
	FPSH_HttpDataTable* FoundData = DataTable->FindRow<FPSH_HttpDataTable>(RowName, TEXT("Looking up player data"));

	return *FoundData;
}

void UPSH_GameInstance::SetdataUpdatae(FPSH_HttpDataTable data)
{

}
