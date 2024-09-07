// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_PlayerState.h"

void ABS_PlayerState::SetPlayerData(FPSH_HttpDataTable data)
{
    playerData = data;
}

void ABS_PlayerState::SetIsFinalSelect(bool value)
{
    isFinalSelect = value;
}