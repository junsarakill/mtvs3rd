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
	// pc 플레이 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category="Default|Values")
	bool isPlayOnPC = false;

	// 눕기 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category="Default|Values")
	bool isFall = false;

	// 이동 방향
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category="Default|Values")
	float horizontal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category="Default|Values")
	float vertical;

	// 컨트롤러 트랜스폼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category="Default|Values")
	FTransform leftControllerTR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category="Default|Values")
	FTransform rightControllerTR;

protected:


public:
	virtual void NativeUpdateAnimation(float deltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;
};
