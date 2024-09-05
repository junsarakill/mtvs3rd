// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_Hand.h"
#include <MotionControllerComponent.h>
#include "Components/SkeletalMeshComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <JBS/BS_GrabComponent.h>
#include "JBS/BS_VRPlayer.h"
#include <Components/WidgetInteractionComponent.h>
#include "Components/ArrowComponent.h"

// Sets default values
ABS_Hand::ABS_Hand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	motionRoot = CreateDefaultSubobject<USceneComponent>(TEXT("motionRoot"));
	// motionRoot->SetupAttachment(motionController);
	SetRootComponent(motionController);

	motionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("motionController"));
	motionController->SetupAttachment(motionRoot);
	// SetRootComponent(motionController);


	handRoot = CreateDefaultSubobject<USceneComponent>(TEXT("handRoot"));
	handRoot->SetupAttachment(motionController);

	// 에임 컨트롤러
	aimMC = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("aimMC"));
	aimMC->SetupAttachment(motionRoot);

	uiInteractComp = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("uiInteractComp"));
	uiInteractComp->SetupAttachment(aimMC);
}
// Called when the game starts or when spawned

void ABS_Hand::BeginPlay()
{
	Super::BeginPlay();

	ENABLE_RAY = ENABLE_RAY;
}

void ABS_Hand::SetController(EMotionControllerType type)
{
	cType = type;
	// 컨트롤러 데이터 찾기
	for(auto fct : typeData)
	{
		if(fct.type == cType)
		{
			// 왼손 오른손 데이터 설정

			// left, right 정하기
			FString enumStr = UEnum::GetValueAsString(fct.type);
			int32 idx = enumStr.Find(TEXT("::"));

			FString cTypeStr = enumStr.RightChop(idx + 2);
			motionController->MotionSource = FName(cTypeStr);


			SetHandMesh(cType);
			handMesh->SetSkeletalMesh(fct.mesh);
			handMesh->SetRelativeLocationAndRotation(fct.loc, fct.rot);
			
			// 에임 컨트롤러 설정
			aimMC->MotionSource = FName(cTypeStr + TEXT("Aim"));
			uiInteractComp->PointerIndex = type == EMotionControllerType::LEFT ? 0 : 1;


			break;
		}
	}
}

// Called every frame
void ABS_Hand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// 레이 활/비
void ABS_Hand::SetEnableRay(bool value)
{
	enableRay = value;
	uiInteractComp->bShowDebug = ENABLE_RAY;
}

void ABS_Hand::SetGrabActor(ABS_GrabbableActor *actor)
{
	check(actor);
	// if(isGrab)
	// 	return;
	isGrab = true;
	grabActor = actor;
}

bool ABS_Hand::TryGrab()
{
	bool hasGrab = false;
	// 가까운 그랩 컴포 가져오기
	auto* grabComp = FindGrabComponentNearHand();
	if(grabComp)
	{
		// 잡기 시도
		hasGrab = grabComp->TryGrab(motionController);
		if(hasGrab)
		{
			// 잡기
			curGrabComp = grabComp;

			// 주인의 반대 손이 같은걸 잡고 있다면 해제 시키기
			auto* owner = Cast<ABS_VRPlayer>(this->GetOwner());
			auto* otherHand = cType == EMotionControllerType::LEFT ? owner->rightController : owner->leftController;
			
			if(otherHand->curGrabComp == this->curGrabComp)
				otherHand->curGrabComp = nullptr;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, -1.f, FColor::Green, TEXT("잡을게 없음"));
	}
	

    return hasGrab;
}
bool ABS_Hand::TryRelease()
{
	if(!curGrabComp) return false;

	// 놓기 시도
	bool isSuccess = curGrabComp->TryRelease();
	// 놓았으면 관계 끊기
	if(isSuccess)
		curGrabComp = nullptr;

    return isSuccess;
}
UBS_GrabComponent *ABS_Hand::FindGrabComponentNearHand()
{
	check(motionController);
	// 주변 잡을 만한 거 찾기
	// 스피어 trace 하기
	// 시작 위치
	FVector gripLocation = motionController->GetComponentLocation();
	// 범위 : grapRadius
	TArray<FHitResult> outHitResults;
	FCollisionShape sphereCol = FCollisionShape::MakeSphere(grabRadius);
	ECollisionChannel traceChl = ECC_Visibility;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	// 히트 하는 위치 설정
	FVector startLocation = gripLocation;
	FVector endLocation = gripLocation;
	
	bool isHit = GetWorld()->SweepMultiByChannel(
		outHitResults,
		startLocation,
		endLocation,
		FQuat::Identity,
		traceChl,
		sphereCol,
		params
	);

	float minDis = FLT_MAX;
	UBS_GrabComponent* nearestGrabComp = nullptr;

	if(isHit)
	{
		for(const FHitResult outHit : outHitResults)
		{
			AActor* hitActor = outHit.GetActor();
			if(hitActor)
			{
				// 액터의 모든 잡기 컴포넌트 가져오기
				TArray<UActorComponent*> grabComps = hitActor->K2_GetComponentsByClass(UBS_GrabComponent::StaticClass());
				if(grabComps.Num() <= 0) continue;
				// 가장 가까운 잡기 컴포넌트 구하기
				for(auto* comp : grabComps)
				{
					// 잡기 컴포넌트에 하기
					UBS_GrabComponent* grabComp = CastChecked<UBS_GrabComponent>(comp);
					if(!grabComp) continue;

					// 최소 길이 계산
					float dis = FVector::Dist(grabComp->GetComponentLocation(), gripLocation);
					if(dis < minDis)
					{
						minDis = dis;
						nearestGrabComp = grabComp;
					}
				}
			}
		}
		// 계산 종료
	}

	// 디버그용 잡기 범위 시각화
	if(enableDebugGrabSphere)
	{
		DrawDebugSphere(
			GetWorld(),
			startLocation,
			grabRadius,
			24,
			FColor::Green,
			false,
			-1.0f
		);
	}

    return nearestGrabComp;
}

void ABS_Hand::EventPressLMB()
{
	uiInteractComp->PressPointerKey(EKeys::LeftMouseButton);
}
void ABS_Hand::EventReleaseLMB()
{
	uiInteractComp->ReleasePointerKey(EKeys::LeftMouseButton);
}