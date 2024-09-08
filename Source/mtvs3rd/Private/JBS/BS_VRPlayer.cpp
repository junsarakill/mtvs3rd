// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_VRPlayer.h"
#include "Camera/CameraComponent.h"
#include <MotionControllerComponent.h>
#include <EnhancedInputSubsystems.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <JBS/BS_PlayerState.h>

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
		PS->IS_FINAL_SELECT = enableDebugFinalSelect;
	}
}

// Called every frame
void ABS_VRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// @@ 디버그단
	// GEngine->AddOnScreenDebugMessage(-1, -1.f, FColor::Green, FString::Printf(TEXT("액터 rot : %s"), *GetActorRotation().ToString()));
	// GEngine->AddOnScreenDebugMessage(-1, -1.f, FColor::Yellow, FString::Printf(TEXT("액터 moveDir : %s"), ));
	FVector debugLoc = vrHMDCam->GetComponentLocation() + vrHMDCam->GetForwardVector()*500.f + vrHMDCam->GetRightVector() * - 200.f;
	
	FString velStr = GetVelocity().ToString();
	int pid = PS->GetPlayerData().Id;
	// 
	float vrRootHeight = vrRoot->GetRelativeLocation().Z;
	
	// 카메라 키
	float vrHMDHeight = this->GetActorLocation().Z - vrHMDCam->GetComponentLocation().Z;
	
	
	FString str = FString::Printf(TEXT("액터 moveDir : %s\n액터 vel : %s\n플레이어 Id : %d\nvrRoot height : %.2f\nhmd height : %.2f")
		, *moveDir.ToString(), *velStr, pid, vrRootHeight, vrHMDHeight);
	DrawDebugString(GetWorld(), debugLoc, str, nullptr, FColor::Green, 0.f, true);
	

	// 이동 방향대로 이동
	AddMovementInput(moveDir, 1);
	// if(moveDir != FVector::ZeroVector)
	// 	moveDir = FVector::ZeroVector;

	
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
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;
}

void ABS_VRPlayer::SetMoveDir(FVector2D dir)
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
		bool isRight = value > 0.f;
		SnapTurn(isRight);
	}
	// @@나중엔 자연스러운 회전?
	else
	{
		
	}
}

void ABS_VRPlayer::SnapTurn(bool isRight)
{
	// z 축으로 회전
	FRotator turnRot = FRotator(0, snapTurnDeg * (isRight ? 1 : -1) ,0);

	// AddControllerYawInput(snapTurnDeg * (isRight ? 1 : -1));
	// SetActorRotation(GetActorRotation() + turnRot);
	AddActorWorldRotation(turnRot);

	
}

