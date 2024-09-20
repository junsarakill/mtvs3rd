// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_PlayerState.h"
#include "PSH/PSH_HttpDataTable.h"

void ABS_PlayerState::SetIsAlreadySelect(bool value)
{
    isAlreadySelect = value;
}

//FPSH_HttpDataTable ABS_PlayerState::GetPlayerData()
//{
//    // syncMap.GetKeys(TSet<int, Allocator> &OutKeys)
//    // 구조체 화 하고 return
////    FPSH_HttpDataTable playerD(id, name, age, gender, mbti, blood, )
//}

void ABS_PlayerState::SetPlayerData(FPSH_HttpDataTable data) 
{
    playerData = data;
}

void ABS_PlayerState::SetIsFinalSelect(bool value)
{
    isFinalSelect = value;
}