// Fill out your copyright notice in the Description page of Project Settings.


#include <JBS/BS_Utility.h>
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "PSH/PSH_GameInstance.h"
#include "PSH/PSH_HttpDataTable.h"
#include "Templates/Casts.h"
#include <PSH/PSH_Mtvs3rdGameModBase.h>
#include <cfloat>
#include <JBS/BS_PlayerState.h>

APSH_Mtvs3rdGameModBase *UBS_Utility::GetGM(UWorld* world)
{
    auto* gm = Cast<APSH_Mtvs3rdGameModBase>(world->GetAuthGameMode());

    return gm;
}

UPSH_GameInstance *UBS_Utility::GetGI(UWorld *world)
{
    return world->GetGameInstance<UPSH_GameInstance>();
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

bool UBS_Utility::TryGetPlayerData(UWorld* world, int id, FPSH_HttpDataTable& outData)
{
    // id 를 key 해서 모든 ps 가져와서 찾아오기
    TArray<TObjectPtr<APlayerState>> tempAllPS = world->GetGameState()->PlayerArray;
	TArray<ABS_PlayerState*> allPS;
	Algo::Transform(tempAllPS, allPS, [](TObjectPtr<APlayerState> temp){
		return Cast<ABS_PlayerState>(temp);
	});

    bool result = false;

	//캐스트 후
    for (ABS_PlayerState *ps : allPS)
    {
        result = ps && ps->ID == id;
        // id 가져오기
        if(result)
        {
            outData = ps->GetPlayerData();
            break;
        }
	}

    return result;
}