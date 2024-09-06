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
	,DUMMY = 4
};

USTRUCT(BlueprintType)
struct FProfileData
{
	GENERATED_BODY()
	
	FString name;
	EPlayerType type;
	int32 syncPercent;

	FProfileData() {}

	FProfileData(FString name, int32 percent, FString gender)
	{
		this->name = name;
		type = gender == TEXT("man") ? EPlayerType::MALE1 :EPlayerType::FEMALE1;
		syncPercent = percent;
	}
};


UCLASS()
class MTVS3RD_API UBS_Utility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
