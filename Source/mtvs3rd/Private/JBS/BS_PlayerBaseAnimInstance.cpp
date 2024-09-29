// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_PlayerBaseAnimInstance.h"
#include "Net/UnrealNetwork.h"


void UBS_PlayerBaseAnimInstance::NativeUpdateAnimation(float deltaTime)
{
    Super::NativeUpdateAnimation(deltaTime);

    // GEngine->AddOnScreenDebugMessage(-1, -1.f, FColor::Green, FString::Printf(TEXT("h : %.2f"), horizontal));
}

void UBS_PlayerBaseAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UBS_PlayerBaseAnimInstance, isPlayOnPC);
    DOREPLIFETIME(UBS_PlayerBaseAnimInstance, isFall);

    DOREPLIFETIME(UBS_PlayerBaseAnimInstance, horizontal);
    DOREPLIFETIME(UBS_PlayerBaseAnimInstance, vertical);

    DOREPLIFETIME(UBS_PlayerBaseAnimInstance, leftControllerTR);
    DOREPLIFETIME(UBS_PlayerBaseAnimInstance, rightControllerTR);
}