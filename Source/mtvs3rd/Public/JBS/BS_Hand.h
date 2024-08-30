// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BS_Hand.generated.h"

UENUM(BlueprintType)
enum class EMotionControllerType : uint8
{
	LEFT
	,RIGHT
};

USTRUCT(BlueprintType)
struct FControllerType
{
	GENERATED_BODY()

	// 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	EMotionControllerType type;
	// 메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	USkeletalMesh* mesh;
	// 위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	FVector loc;
	// 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	FRotator rot;
};

UCLASS()
class MTVS3RD_API ABS_Hand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABS_Hand();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class UMotionControllerComponent* motionController;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class USkeletalMeshComponent* handMesh;
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	// class UXRDeviceVisualizationComponent* xrDVisualComp;
	

// 컨트롤러 종류
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	EMotionControllerType cType;

// 컨트롤러 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	TArray<FControllerType> typeData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetController(EMotionControllerType type);
};
