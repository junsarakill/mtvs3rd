// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_GrabHoverUIActor.h"
#include "Components/WidgetComponent.h"
#include "Engine/Engine.h"

void ABS_GrabHoverUIActor::BeginPlay()
{
	Super::BeginPlay();

    IS_VISIBLE = false;
}

void ABS_GrabHoverUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(IS_VISIBLE)
    {
        BillboardUI(hoverUIComp);
        FixSize(hoverUIComp, desireDistance);

        // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("asd"));
        // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(
        //     TEXT("회전: %s, \n스케일: %s\nscale: %s")
        //     , *hoverUIComp->GetComponentRotation().ToString()
        //     , *hoverUIComp->GetComponentScale().ToString()
        //     , *uiDefaultScale.ToString()
        // ));
    }
}

void ABS_GrabHoverUIActor::SetVisibleHoverUI(bool value)
{
    hoverUIComp->SetHiddenInGame(value);

    // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%d asd"), value));
}

void ABS_GrabHoverUIActor::SetIsVisible(bool value)
{
    isVisible = value;

    SetVisibleHoverUI(!IS_VISIBLE);
}