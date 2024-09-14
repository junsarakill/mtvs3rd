// Fill out your copyright notice in the Description page of Project Settings.


#include <JBS/BS_GrabComponent.h>
#include "Kismet/KismetMathLibrary.h"
#include <MotionControllerComponent.h>
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <Haptics/HapticFeedbackEffect_Curve.h>

// Sets default values for this component's properties
UBS_GrabComponent::UBS_GrabComponent()
{
	// XXX tick disable
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UBS_GrabComponent::BeginPlay()
{
	Super::BeginPlay();

	// 물리 킬 수 있는지 확인
	SetShouldSimulateOnDrop();
	// 콜리전 변경
	auto* phyComp = Cast<UPrimitiveComponent>(GetAttachParent());
	check(phyComp);
	phyComp->SetCollisionProfileName(FName(TEXT("VRPhysicsActor")));
}


// Called every frame
void UBS_GrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBS_GrabComponent::TryGrab(UMotionControllerComponent *mc)
{
	check(mc);

	switch(grabType)
	{
		case EGrabType::Free:
			isHeld = GrabNormal(mc);
			break;
		case EGrabType::Snap:
			isHeld = GrabSnap(mc);
			break;
		case EGrabType::Custom:
			isHeld = true;
			break;
	}
	// 잡기 성공시
	if(isHeld)
	{
		heldController = mc;
		// 진동
		// 진동할 컨트롤러 구하기
		EControllerHand handType = GetHeldbyHand();

		auto* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		check(pc);
		pc->PlayHapticEffect(grapHapticPrefab, handType);
	}

    return isHeld;
}

bool UBS_GrabComponent::GrabNormal(UMotionControllerComponent * mc)
{
	SetPrimitiveCompPhysics(false);
	// 컨트롤러에 붙이기

	return AttachToMotionController(mc);
}

bool UBS_GrabComponent::GrabSnap(UMotionControllerComponent * mc)
{
	// 일반 잡기
	bool result = GrabNormal(mc);
	// GrabComponent의 상대 위치에 맞춰 잡고 있는 액터를 정렬
	auto* parent = GetAttachParent();
	// 회전
	FRotator newRot = UKismetMathLibrary::NegateRotator(this->GetRelativeRotation());
	parent->SetRelativeRotation(newRot);

	// 위치 ==  (포인트 - 부모) * -1.f (리버스) + 컨트롤러 위치
	FVector newLoc = (this->GetComponentLocation() - parent->GetComponentLocation()) * -1.f;
	newLoc += mc->GetComponentLocation();
	parent->SetWorldLocation(newLoc);

	return result;
}

// 놓으면 true
bool UBS_GrabComponent::TryRelease()
{
	switch (grabType)
	{
		case EGrabType::None:
			break;
		// 둘이 같음
		case EGrabType::Free:
		case EGrabType::Snap:
		{
			// 물리 킬 수 있는지 확인
			if(canSimulateOnDrop)
				SetPrimitiveCompPhysics(true);

			GetAttachParent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			break;
		}
		case EGrabType::Custom:
			break;
	}
	isHeld = false;

	return !isHeld;
}

void UBS_GrabComponent::SetPrimitiveCompPhysics(bool value)
{
	auto* phyComp = Cast<UPrimitiveComponent>(GetAttachParent());
	check(phyComp);
	phyComp->SetSimulatePhysics(value);
}

void UBS_GrabComponent::SetShouldSimulateOnDrop()
{
	auto* phyComp = Cast<UPrimitiveComponent>(GetAttachParent());
	check(phyComp);

	canSimulateOnDrop = phyComp->IsAnySimulatingPhysics();
}

bool UBS_GrabComponent::AttachToMotionController(UMotionControllerComponent *mc)
{
	// 컨트롤러에 부모 메시 붙이기
	bool isAttach = GetAttachParent()->AttachToComponent(mc, FAttachmentTransformRules::KeepWorldTransform);
	if(!isAttach)
	{
		// 어태치 실패 로그
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("%s attach \n to \n %s is Failed")
			, *UKismetSystemLibrary::GetDisplayName(GetAttachParent()), *UKismetSystemLibrary::GetDisplayName(mc)));
	}

    return isAttach;
}

EControllerHand UBS_GrabComponent::GetHeldbyHand()
{
	check(heldController);
	EControllerHand hand = heldController->MotionSource == FName(TEXT("Left")) 
		? EControllerHand::Left : EControllerHand::Right;

    return hand;
}
