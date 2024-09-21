// Fill out your copyright notice in the Description page of Project Settings.


#include <JBS/BS_Utility.h>
#include "Engine/World.h"
#include <PSH/PSH_Mtvs3rdGameModBase.h>

APSH_Mtvs3rdGameModBase *UBS_Utility::GetGM(UWorld* world)
{
    auto* gm = Cast<APSH_Mtvs3rdGameModBase>(world->GetAuthGameMode());

    return gm;
}