// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Kismet/BlueprintFunctionLibrary.h>
#include <JBS/BS_PlayerBaseAnimInstance.h>
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

// 플레이어 외형 데이터
USTRUCT(BlueprintType)
struct FPlayerAppearanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	EPlayerType type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	class USkeletalMesh* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	TSubclassOf<class UBS_PlayerBaseAnimInstance> anim;

	FPlayerAppearanceData() {}
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
		type = gender == TEXT("Man") ? EPlayerType::MALE1 : EPlayerType::FEMALE1;
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
	static class UPSH_GameInstance *GetGI(UWorld *world);

        // 컴포넌트 중 가장 가까운 거 구하기
	static class UActorComponent *GetNearestGrabComp(TArray<UActorComponent *> comps, FVector targetLoc);

	// id로 플레이어 스테이트 가져오기
	static class ABS_PlayerState *TryGetPlayerState(UWorld *world, int id);
};
