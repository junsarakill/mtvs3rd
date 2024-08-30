// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_Hand.h"
#include <MotionControllerComponent.h>
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABS_Hand::ABS_Hand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	motionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("motionController"));
	motionController->SetupAttachment(RootComponent);

	handMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("handMesh"));
	handMesh->SetupAttachment(motionController);
}

// Called when the game starts or when spawned
void ABS_Hand::BeginPlay()
{
	Super::BeginPlay();

	SetController(cType);

}

void ABS_Hand::SetController(EMotionControllerType type)
{
	// 컨트롤러 데이터 찾기
	for(auto ff : typeData)
	{
		if(ff.type == type)
		{
			// 왼손 오른손 데이터 설정
			motionController->MotionSource = type == EMotionControllerType::LEFT ? FName(TEXT("Left")) : FName(TEXT("Right"));
			handMesh->SetSkeletalMesh(ff.mesh);
			handMesh->SetRelativeLocationAndRotation(ff.loc, ff.rot);
		}
	}
}

// Called every frame
void ABS_Hand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

