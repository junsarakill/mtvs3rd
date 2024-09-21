// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Kismet/BlueprintFunctionLibrary.h>
#include "BS_Utility.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerType : uint8
{
	MALE1 = 0
	,FEMALE1 = 1
	,MALE2
	,FEMALE2
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
		// @@ 젠더에 더불어 나이대로 얼터체크 필요
		type = gender == TEXT("남") ? EPlayerType::MALE1 : EPlayerType::FEMALE1;
		syncPercent = percent;
	}
};

UENUM(BlueprintType)
enum class EFinalSelectType : uint8
{
	NORMAL = 0
	,DUMMY = 1
};


UCLASS()
class MTVS3RD_API UBS_Utility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static class APSH_Mtvs3rdGameModBase* GetGM(UWorld* world);

	// 컴포넌트 중 가장 가까운 거 구하기
	static class UActorComponent *GetNearestGrabComp(TArray<UActorComponent *> comps, FVector targetLoc);
};
