// Fill out your copyright notice in the Description page of Project Settings.


#include <JBS/BS_Hand.h>
#include <MotionControllerComponent.h>
#include "Components/SkeletalMeshComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <JBS/BS_GrabComponent.h>
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "JBS/BS_GrabbableActor.h"
#include "JBS/BS_VRPlayer.h"
#include <Components/WidgetInteractionComponent.h>
#include "Components/ArrowComponent.h"
#include "Templates/Casts.h"
#include <JBS/BS_PlayerState.h>
#include <JBS/BS_ProfileWorldUIActor.h>
#include <JBS/BS_Utility.h>
#include <JBS/BS_FinalSelectComponent.h>
#include <PSH/PSH_Mtvs3rdGameModBase.h>
#include <JBS/BS_GrabHoverUIActor.h>


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

	profileUIPos = CreateDefaultSubobject<UArrowComponent>(TEXT("profileUIPos"));
	profileUIPos->SetupAttachment(aimMC);

	// 최종 선택 컴포넌트 추가
	fsComp = CreateDefaultSubobject<UBS_FinalSelectComponent>(TEXT("fsComp"));
}
// Called when the game starts or when spawned



void ABS_Hand::BeginPlay()
{
	Super::BeginPlay();

	// ray 초기값 설정
	SetEnableRay(ENABLE_RAY);

	// 
	// if(!HasAuthority())
	// {
	// 	uiInteractComp->SetActive(false);
	// }
	ownerPlayer = Cast<ABS_VRPlayer>(this->GetOwner());
	if(ownerPlayer)
	{
		if(!ownerPlayer->IsLocallyControlled())
		{
			uiInteractComp->DestroyComponent();
		}
	}
}

void ABS_Hand::SetController(EMotionControllerType type, ABS_VRPlayer* player)
{
	cType = type;
	// 컨트롤러 데이터 찾기
	for(FControllerType fct : typeData)
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
			if(uiInteractComp)
				uiInteractComp->PointerIndex = type == EMotionControllerType::LEFT ? 1: 2;

			break;
		}
	}

	// 주인 설정
	check(player);
	ownerPlayer = player;
}

// Called every frame
void ABS_Hand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 원거리 물건 잡기용 힛
	FindGrabComponentByRay(curFindGrabComp);
}

void ABS_Hand::SetRayInteractDis(float value)
{
	rayInteractDis = value;
	// uiinteractcomp 도 동기화
	if(uiInteractComp)
		uiInteractComp->InteractionDistance = RAY_INTERACT_DIS;
}
// 레이 활/비
void ABS_Hand::SetEnableRay(bool value)
{
	enableRay = value;
	if(uiInteractComp)
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
		hasGrab = Grab(grabComp);
	}
	else
	{
		// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("주변 잡을게 없음"));
		// trigger 하고 있으면 원거리 잡기 시도
		if(CAN_RANGE_GRAB && curFindGrabComp)
		{
			hasGrab = Grab(curFindGrabComp);
			// @@ snap 아니면 내 손 위치로 가져오게 바꿀 필요있음.
		}
		else
		{
			// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("crg : %s\ncomp : %s")
			// , CAN_RANGE_GRAB ? TEXT("true") : TEXT("false")
			// , curFindGrabComp ? *curFindGrabComp->GetName() : TEXT("nullptr")
			// ));
			// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("원거리도 잡을게 없음"));
		}
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
		for(const FHitResult &outHit : outHitResults)
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
	if(uiInteractComp)
		uiInteractComp->PressPointerKey(EKeys::LeftMouseButton);
}
void ABS_Hand::EventReleaseLMB()
{
	if(uiInteractComp)
		uiInteractComp->ReleasePointerKey(EKeys::LeftMouseButton);

	// 플레이어 감지해서 프로필 뜨게하기
	LineTracePlayer();
}
void ABS_Hand::LineTracePlayer()
{
	FHitResult outHit;
	ECollisionChannel traceChl = ECC_Camera;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(Cast<ABS_VRPlayer>(this->GetOwner()));
	// 히트 하는 위치 설정
	FVector startLocation = aimMC->GetComponentLocation();
	FVector endLocation = startLocation + aimMC->GetForwardVector() * RAY_INTERACT_DIS;
	bool isHit = GetWorld()->LineTraceSingleByChannel(
		outHit,
		startLocation,
		endLocation,
		traceChl,
		params
	);
	
	if(isHit)
	{
		// XXX 프로토타입용
		// 대상이 더미라면
		if(outHit.GetActor()->ActorHasTag(FName("Dummy")))
		{
			// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("더미 감지"));
			auto* gm = UBS_Utility::GetGM(GetWorld());
			FPSH_HttpDataTable dData = gm->GetData(dummyID);
			
			// FString debugWorldStr = FString::Printf(TEXT("id : %d\nname : %s\ngender : %s"), dData.Id, *dData.Name, *dData.Gender);
			// DrawDebugString(GetWorld(), this->GetActorLocation(), debugWorldStr, nullptr, FColor::Green, 30.f, true);

			// 내 손에 프로필 ui 생성
			SpawnProfileUI(dData);
			// 최종 선택인 경우 선택 UI도 생성
			fsComp->SRPC_TrySpawnSelectConfirmUI(dData.Id);
			// fsComp->TrySpawnSelectConfirmUI(dData.Id);
		}
		// 대상이 플레이어라면 프로필 ui 생성->최종 선택이면 선택 ui 도 생성
		else if(outHit.GetActor()->ActorHasTag(FName("Player")))
		{
			auto* otherPlayer = Cast<ABS_VRPlayer>(outHit.GetActor());
			check(otherPlayer);
			SRPC_SpawnProfileUI(otherPlayer);
		}
	}
}

// 프로필 ui 생성
void ABS_Hand::SpawnProfileUI(FPSH_HttpDataTable otherPlayerData)
{
	if(profileUIActor) return;

	profileUIActor = GetWorld()->SpawnActor<ABS_ProfileWorldUIActor>(profileUIActorPrefab, profileUIPos->GetComponentLocation(), profileUIPos->GetComponentRotation());
	profileUIActor->AttachToComponent(aimMC, FAttachmentTransformRules::KeepWorldTransform);

	// ui 컴포넌트 캐시
	profileUIActor->SetProfileUI();

	// 싱크로율 구하기
	// 내 정보
	auto* player = Cast<ABS_VRPlayer>(GetOwner());
	auto* ps = player->GetPlayerState<ABS_PlayerState>();
	check(ps);
	// ps 로 뭔가하기
	auto ownerData = ps->GetPlayerData();
	float sync = -1.f;
	// 상대 id 찾아서 싱크로율 가져오기
	if(ownerData.otherUserID1 == otherPlayerData.Id)
	{
		sync = ownerData.syncPercentID1;
		
	}
	else if(ownerData.otherUserID2 == otherPlayerData.Id)
	{
		sync = ownerData.syncPercentID2;
	}
	
	// 프로필 데이터 구조체
	FProfileData data(otherPlayerData.Name,(int) sync, otherPlayerData.Gender);
	// ui에 값 설정
	profileUIActor->SetProfileUIValue(data);
}

void ABS_Hand::DeleteProfileUI()
{
	if(!profileUIActor) return;

	// 액터 제거 및 초기화
	profileUIActor->Destroy();
	profileUIActor = nullptr;
}

void ABS_Hand::SetCanRangeGrab(bool value)
{
    bool check = value;

    if (isGrab || curGrabComp || grabActor)
    {
        check = false;
    }

    canRangeGrab = check;
}
void ABS_Hand::FindGrabComponentByRay(UBS_GrabComponent*& findGrabComp)
{
	if(!CAN_RANGE_GRAB)
	{
		CUR_FIND_GRAB_COMP = nullptr;
		return;
	}

	FHitResult outHit;
	ECollisionChannel traceChl = ECC_Visibility;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	// 히트 하는 위치 설정
	FVector startLocation = aimMC->GetComponentLocation();
	FVector endLocation = startLocation + aimMC->GetForwardVector() * RAY_INTERACT_DIS;
	bool isHit = GetWorld()->LineTraceSingleByChannel(
		outHit,
		startLocation,
		endLocation,
		traceChl,
		params
	);
	
	if(isHit)
	{
		// 액터의 모든 잡기 컴포넌트 가져오기
		TArray<UActorComponent*> grabComps = outHit.GetActor()->K2_GetComponentsByClass(UBS_GrabComponent::StaticClass());
		// 가장 가까운 잡기 컴포 구하기
		CUR_FIND_GRAB_COMP = Cast<UBS_GrabComponent>(UBS_Utility::GetNearestGrabComp(grabComps, startLocation));
	}
	else {
		CUR_FIND_GRAB_COMP = nullptr;
	}
}

bool ABS_Hand::Grab(UBS_GrabComponent* grabComp)
{
	// 잡기 시도
	bool hasGrab = grabComp->TryGrab(motionController);
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

	return hasGrab;
}

void ABS_Hand::SetCurFindGrabComp(UBS_GrabComponent *value)
{
    // 값이 변경되는 경우 이전 컴포넌트 hover ui 비활성화
    if (curFindGrabComp != value && curFindGrabComp)
    {
        auto* gcompOwner = CUR_FIND_GRAB_COMP->GetOwner<ABS_GrabbableActor>();
		check(gcompOwner);
		gcompOwner->grabHoverUIActor->IS_VISIBLE = false;
    }

	// 값 설정
    curFindGrabComp = value;
	
	// 새 값 hover ui 활성화
	if(curFindGrabComp != nullptr)
	{
		auto* gcompOwner = CUR_FIND_GRAB_COMP->GetOwner<ABS_GrabbableActor>();
		check(gcompOwner);
		gcompOwner->grabHoverUIActor->IS_VISIBLE = true;
	}
}
void ABS_Hand::SRPC_SpawnProfileUI_Implementation(ABS_VRPlayer *otherPlayer)
{
    auto* otherPS = otherPlayer->GetPlayerState<ABS_PlayerState>();
	check(otherPS);
	auto otherPlayerData = otherPS->GetPlayerData();
	// 클라에 프로필 ui 생성
	MRPC_SpawnProfileUI(otherPlayerData);
}

void ABS_Hand::MRPC_SpawnProfileUI_Implementation(FPSH_HttpDataTable profileData) {
	SpawnProfileUI(profileData);
	// 최종 선택인 경우 선택 UI도 생성
	fsComp->SRPC_TrySpawnSelectConfirmUI(profileData.Id);
}
