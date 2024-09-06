// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_HttpDataTable.h"

void FPSH_HttpDataTable::PrintStruct()
{
	UE_LOG(LogTemp,Warning,TEXT("Id : %d Name : %s Age : %d Gender : %s MBTI : %s Blood : %s FromUserID1 : %d synchro_1 : %f Target_2_Id : %d synchro_2 : %f "),Id, *Name , Age, *Gender, *MBTI, *Blood, otherUserID1, syncPercentID1, otherUserID2, syncPercentID2);
}
