// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_VRPlayer.h"
#include "Camera/CameraComponent.h"
#include <MotionControllerComponent.h>
#include <EnhancedInputSubsystems.h>
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "JBS/BS_Hand.h"
#include "JBS/BS_Utility.h"
#include "Kismet/KismetMathLibrary.h"
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

	SetMoveSpeed(moveSpeed);

	if(enableDebugFinalSelect)
	{
		// PS->IS_FINAL_SELECT = enableDebugFinalSelect;
	}

	if(playOnPC)
	{
		vrRoot->SetRelativeLocation(FVector(-276,0,138));
		vrRoot->SetRelativeRotation(FRotator(-15,0,0));
		
	}
	this->bUseControllerRotationYaw = playOnPC;
	vrHMDCam->bUsePawnControlRotation = playOnPC;

	//@@ 플레이어 성별 가져와서 타입 판별후 메시,애니 설정
	// FIXME 성별 + 조건 하나 더 필요
	EPlayerType pType = DATA.Gender == TEXT("Man") ? EPlayerType::MALE1 : EPlayerType::FEMALE1;
	SetPlayerAppearance(pType);

	GetAnim()->isPlayOnPC = playOnPC;
}

// Called every frame
void ABS_VRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// XXX 디버그단
	if(enableViewPlayerStat)
	{
		FVector debugLoc = vrHMDCam->GetComponentLocation() + vrHMDCam->GetForwardVector()*500.f + vrHMDCam->GetRightVector() * - 200.f;
		
		FString velStr = GetVelocity().ToString();
		// 
		float vrRootHeight = vrRoot->GetRelativeLocation().Z;
		
		// 카메라 키
		float vrHMDHeight = this->GetActorLocation().Z - vrHMDCam->GetComponentLocation().Z;
		
		
		FString str = FString::Printf(TEXT("액터 moveDir : %s\n액터 vel : %s\n플레이어 Id : %d\nvrRoot height : %.2f\nhmd height : %.2f")
			, *moveDir.ToString(), *velStr, DATA.Id, vrRootHeight, vrHMDHeight);
		DrawDebugString(GetWorld(), debugLoc, str, nullptr, FColor::Green, 0.f, true);
	}

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
	else 
	{
		// vrHMDCam->GetComponentRotation()
		// this->AddActorWorldRotation(FRotator DeltaRotation)

	}
	

	// 이동 방향대로 이동
	AddMovementInput(moveDir, 1);
	// if(moveDir != FVector::ZeroVector)
	// 	moveDir = FVector::ZeroVector;

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

// Called to bind functionality to input
void ABS_VRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABS_VRPlayer::SetPS(ABS_PlayerState *value)
{
	auto* myPS = this->GetPlayerState<ABS_PlayerState>();
	check(myPS);
	// ps 로 뭔가하기
	ps = myPS;
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
	// moveDir = vrHMDCam->GetComponentRotation().RotateVector(inputDir);
	// // 2d 이동으로 정규화
	// moveDir.Z = 0.f;
	// moveDir.Normalize();
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
	// @@나중엔 자연스러운 회전?
	else
	{
		SmoothTurn(value);
	}
}

void ABS_VRPlayer::SnapTurn(bool isRight)
{
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("턴"));
	// z 축으로 회전
	FRotator turnRot = FRotator(0, snapTurnDeg * (isRight ? 1 : -1) ,0);

	// AddControllerYawInput(snapTurnDeg * (isRight ? 1 : -1));
	// SetActorRotation(GetActorRotation() + turnRot);
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

ABS_PlayerState *ABS_VRPlayer::GetPS()
{
    // ps 캐시 안되있으면 가져오기
    if (!ps)
    {
        auto *myPS = this->GetPlayerState<ABS_PlayerState>();
        check(myPS);
        // ps 로 뭔가하기
        ps = myPS;
    }

    return ps;
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
		// FIXME 시간 확인 필요
		GetAnim()->isFall = false;
	}, 5.f, false);
}
// FIXME 이거 좋은 타이밍에 가져오기
FPSH_HttpDataTable ABS_VRPlayer::GetPlayerData()
{
	auto* pc = Cast<APlayerController>(this->GetController());
	if(pc)
	{
		//pc로 뭔가 하기
		auto* aps = pc->GetPlayerState<ABS_PlayerState>();
		if(aps)
		{
			return aps->GetPlayerData();
		}
	}


	return FPSH_HttpDataTable(); 
	return data;
}
class UBS_PlayerBaseAnimInstance *ABS_VRPlayer::GetAnim()
{
    if (!anim)
    {
        anim = Cast<UBS_PlayerBaseAnimInstance>(GetMesh()->GetAnimInstance());
    }

    return anim;
}
