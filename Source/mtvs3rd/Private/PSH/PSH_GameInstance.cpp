// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_GameInstance.h"

void UPSH_GameInstance::SetStartData(FPSH_HttpDataTable data)
{
	PlayerData = data; // ������ ����

	// ���� Name���� �����ϸ� ���� ��������.
	FName RowName = FName(PlayerData.Id); // �̸� ���� 
	DataTable->AddRow(RowName, PlayerData); // ������ ���̺� �߰�.//

	UE_LOG(LogTemp,Warning,TEXT("GameInstance"));
	PlayerData.PrintStruct();
}

void UPSH_GameInstance::SetdataUpdatae(FPSH_HttpDataTable data)
{

}
