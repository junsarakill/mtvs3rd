// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BS_Utility.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerType : uint8
{
	MALE1 = 0
	,FEMALE1 = 1
};


UCLASS()
class MTVS3RD_API UBS_Utility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
