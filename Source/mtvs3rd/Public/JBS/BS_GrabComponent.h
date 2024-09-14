// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Components/SceneComponent.h>
#include <InputCoreTypes.h>
#include "BS_GrabComponent.generated.h"

UENUM(BlueprintType)
enum class EGrabType : uint8
{
	None = 0
	,Free = 1
	,Snap
	,Custom
};

UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class MTVS3RD_API UBS_GrabComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBS_GrabComponent();

protected:
	// 잡기 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	EGrabType grabType = EGrabType::Free;

	// 잡힘 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	bool isHeld = false;

	// 나를 잡고 있는 컨트롤러
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Objects")
	class UMotionControllerComponent* heldController;

	// 진동 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	class UHapticFeedbackEffect_Curve* grapHapticPrefab;

	// 물리 킬 수 있는지 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	bool canSimulateOnDrop = false;

	//XXX 잡기 딜리게이트 

	// 놓기 딜리게이트


	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 잡히기 시도
	bool TryGrab(class UMotionControllerComponent* mc);
	// 일반 잡기
	bool GrabNormal(class UMotionControllerComponent* mc);
	// 스냅 잡기
	bool GrabSnap(class UMotionControllerComponent* mc);

	// 놓기 시도 : 놓으면 true 반환
	bool TryRelease();



	// 부모 액터 물리 여부 설정
	void SetPrimitiveCompPhysics(bool value);

	// 부모 액터가 물리 킬 수 있는지 여부 설정
	void SetShouldSimulateOnDrop();

	// 컨트롤러에 붙이기
	bool AttachToMotionController(class UMotionControllerComponent* mc);

	// 날 잡은 컨트롤러 타입 구하기(좌/우)
	EControllerHand GetHeldbyHand(); 

	
		
};
