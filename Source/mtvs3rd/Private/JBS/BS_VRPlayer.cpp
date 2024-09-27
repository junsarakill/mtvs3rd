// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_VRPlayer.h"
#include "Camera/CameraComponent.h"
#include <MotionControllerComponent.h>
#include <EnhancedInputSubsystems.h>
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "JBS/BS_Hand.h"
#include "JBS/BS_Utility.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "PSH/PSH_HttpDataTable.h"
#include "TimerManager.h"
#include <JBS/BS_PlayerState.h>
#include <JBS/BS_PlayerBaseAnimInstance.h>

// Sets default values
ABS_VRPlayer::ABS_VRPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	vrRoot = CreateDefaultSubobject<USceneComponent>(TEXT("vrRoot"));
	vrRoot->SetupAttachment(RootComponent);

	vrHMDCam = CreateDefaultSubobject<UCameraComponent>(TEXT("vrHMDCam"));
	vrHMDCam->SetupAttachment(vrRoot);
	vrHMDCam->bUsePawnControlRotation = true;

	// 플레이어 ui 위치 1
	playerUIPos1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("playerUIPos1"));
	playerUIPos1->SetupAttachment(vrHMDCam);
	
}

// Called when the game starts or when spawned
void ABS_VRPlayer::BeginPlay()
{
	Super::BeginPlay();

	// playOnPC = !UHeadMountedDisplayFunctionLibrary::IsHMDActive();
    // UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled();

	// 로컬 플레이어
	if(IsLocallyControlled())
	{
		
	}

	SetMoveSpeed(moveSpeed);

	// XXX bp로 대체
	// if(playOnPC)
	// {
	// 	vrRoot->SetRelativeLocation(FVector(-276,0,138));
	// 	vrRoot->SetRelativeRotation(FRotator(-15,0,0));
		
	// }
	// this->bUseControllerRotationYaw = playOnPC;
	// vrHMDCam->bUsePawnControlRotation = playOnPC;
	// GetAnim()->isPlayOnPC = playOnPC;
}

// Called every frame
void ABS_VRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// XXX 디버그단
	if(enableViewPlayerStat)
	{
		if(IsLocallyControlled())
		{
			SRPC_DebugPlayerStat();
			// DrawDebugCapsule(GetWorld(), GetCapsuleComponent()->GetComponentLocation(), GetCapsuleComponent()->GetScaledCapsuleHalfHeight()
			// , GetCapsuleComponent()->GetScaledCapsuleRadius(),FQuat::Identity, FColor::Green, false, -1, 0, 5);
		}
	}
	// pc 버전 캠, 손 위치 설정
	if(playOnPC)
	{
		if(leftController)
		{
			FVector camFV = vrHMDCam->GetForwardVector();
			FVector lookPos = camFV * 1000.f + vrHMDCam->GetComponentLocation();

			FVector newLoc = camFV * 100.f + vrHMDCam->GetComponentLocation();
			FRotator newRot = UKismetMathLibrary::FindLookAtRotation(leftController->GetActorLocation(), lookPos);

			leftController->SetActorLocationAndRotation(newLoc, newRot);
		}
	}

	// 이동 방향대로 이동
	AddMovementInput(moveDir, 1);

	if(this->IsLocallyControlled())
	{
		// 이동 방향 값 애니메이션에 전달
		FVector vel = GetVelocity();
		FVector fv = GetActorForwardVector();
		FVector rv = GetActorRightVector();
		
		GetAnim()->vertical = FVector::DotProduct(fv, vel);
		GetAnim()->horizontal = FVector::DotProduct(rv, vel);

		// 컨트롤러 위치 값 애니메이션에 전달
		GetAnim()->leftControllerTR = leftController->handWorldTR;
		GetAnim()->rightControllerTR = rightController->handWorldTR;
	}

	
}

// solved input action은 bp에서 설정
void ABS_VRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABS_VRPlayer::SetIMC(UInputMappingContext *imc)
{
	auto* pc = Cast<APlayerController>(this->GetController());
	if(pc)
	{
		auto* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if(subSystem)
		{
			subSystem->AddMappingContext(imc, 0);
		}
	}

}

void ABS_VRPlayer::SetMoveSpeed(float value)
{
	moveSpeed = value;
	GetCharacterMovement()->MaxWalkSpeed = MOVE_SPEED;
}

void ABS_VRPlayer::EventMove(FVector2D dir)
{
	// 입력 값
	FVector inputDir = FVector(dir.X,dir.Y,0.f).GetSafeNormal();
	// 카메라의 전방을 기준 축으로 잡기
	moveDir = (vrHMDCam->GetForwardVector() * inputDir.Y) + (vrHMDCam->GetRightVector() * inputDir.X);
	if(!moveDir.IsZero())
		moveDir.Normalize();
}

void ABS_VRPlayer::EventTurn(float value)
{
	// 스냅턴 켜져있으면 스냅턴으로
	if(isSnapTurn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("스냅턴"));
		bool isRight = value > 0.f;
		SnapTurn(isRight);
	}
	// XXX 나중엔 자연스러운 회전?
	else
	{
		SmoothTurn(value);
	}
}

void ABS_VRPlayer::SnapTurn(bool isRight)
{
	// z 축으로 회전
	FRotator turnRot = FRotator(0, snapTurnDeg * (isRight ? 1 : -1) ,0);

	AddActorWorldRotation(turnRot);
}

void ABS_VRPlayer::SmoothTurn(float value)
{
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%.2f"), value));
	this->AddControllerYawInput(value * smoothTurnMulti);
}

void ABS_VRPlayer::EventLookup(FVector2D value)
{
	AddControllerYawInput(value.X);
	AddControllerPitchInput(-value.Y);
	
}

void ABS_VRPlayer::StartTrip()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("넘어짐"));

	GetAnim()->isFall = true;
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager()
		.SetTimer(timerHandle, [this]() mutable
	{
		//타이머에서 할 거
		GetAnim()->isFall = false;
	}, 10.f, false);
}

UBS_PlayerBaseAnimInstance *ABS_VRPlayer::GetAnim()
{
    if (!anim)
        anim = Cast<UBS_PlayerBaseAnimInstance>(GetMesh()->GetAnimInstance());

    return anim;
}

// dore 복제
void ABS_VRPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// DOREPLIFETIME(ABS_VRPlayer, isSetAppearance);
}

void ABS_VRPlayer::SRPC_CalcPlayerType_Implementation(EPlayerType type)
{
	MRPC_CalcPlayerType(type);
}

void ABS_VRPlayer::MRPC_CalcPlayerType_Implementation(EPlayerType pType)
{
	// 해당 타입대로 외형 설정
	SetPlayerAppearance(pType);
}

void ABS_VRPlayer::SRPC_DebugPlayerStat_Implementation()
{
    // 서버단에서 ps 찾아서 str 구성
    auto *ps = this->GetPlayerState<ABS_PlayerState>();
    check(ps);
    // ps 로 뭔가하기
	// 디버그 str 구성
    FString str = FString::Printf(TEXT("id : %d\ngender : %s\nage : %d\n모드 : %s")
		, ps->ID, *ps->gender, ps->age, playOnPC ? TEXT("PC") : TEXT("VR"));

    MRPC_DebugPlayerStat(str);
}

void ABS_VRPlayer::MRPC_DebugPlayerStat_Implementation(const FString &playerStatStr)
{
	// 디버그 용
	FVector debugLoc = vrHMDCam->GetComponentLocation() + vrHMDCam->GetForwardVector()*500.f + vrHMDCam->GetRightVector() * - 200.f;
	FString velStr = GetVelocity().ToString();
	float vrRootHeight = vrRoot->GetRelativeLocation().Z;
	// 카메라 키
	float vrHMDHeight = this->GetActorLocation().Z - vrHMDCam->GetComponentLocation().Z;
	
    DrawDebugString(GetWorld(), debugLoc, playerStatStr, nullptr, FColor::Green, 0.f, true);
}
