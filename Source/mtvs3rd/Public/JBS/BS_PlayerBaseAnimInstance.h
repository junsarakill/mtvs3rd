// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BS_PlayerBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UBS_PlayerBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:


public:
	// 눕기 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	bool isFall = false;

	// 

protected:


public:
};
