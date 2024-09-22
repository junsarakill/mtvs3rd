// Fill out your copyright notice in the Description page of Project Settings.


#include <JBS/BS_Utility.h>
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Templates/Casts.h"
#include <PSH/PSH_Mtvs3rdGameModBase.h>
#include <cfloat>

APSH_Mtvs3rdGameModBase *UBS_Utility::GetGM(UWorld* world)
{
    auto* gm = Cast<APSH_Mtvs3rdGameModBase>(world->GetAuthGameMode());

    return gm;
}

UActorComponent *UBS_Utility::GetNearestGrabComp(TArray<UActorComponent *> comps, FVector targetLoc)
{
    if (comps.Num() <= 0)
        return nullptr;

    float minDis = FLT_MAX;
    UActorComponent* resultComp = nullptr;

    for(auto* comp : comps)
    {
        auto* scomp = CastChecked<USceneComponent>(comp);

        float dis = FVector::Dist(scomp->GetComponentLocation(), targetLoc);
        if(dis < minDis)
        {
            minDis = dis;
            resultComp = scomp;
        }
    }

    return resultComp;
}