// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_BillBoardWorldUIActor.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABS_BillBoardWorldUIActor::ABS_BillBoardWorldUIActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABS_BillBoardWorldUIActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABS_BillBoardWorldUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABS_BillBoardWorldUIActor::BillboardUI(UWidgetComponent *uiComp)
{
	if(!uiComp) return;

	// 로컬 클라이언트 플레이어를 바라보기
	auto* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(pc)
	{
		//pc로 뭔가 하기
		auto cam = pc->PlayerCameraManager;
		if(cam)
		{
			FVector targetLoc = cam->GetCameraLocation();
			FVector worldUILoc = uiComp->GetComponentLocation();
			
			FRotator lookRot = (targetLoc - worldUILoc).Rotation();
			uiComp->SetWorldRotation(lookRot);
		}
	}
}
