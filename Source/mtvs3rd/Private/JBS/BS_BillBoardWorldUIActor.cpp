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

void ABS_BillBoardWorldUIActor::FixSize(class UWidgetComponent *uiComp, float desireDis)
{
	if(!uiComp) return;

	auto* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(pc)
	{
		//pc로 뭔가 하기
		auto cam = pc->PlayerCameraManager;
		if(cam)
		{
			FVector camLoc = cam->GetCameraLocation();
			// 크기 일정하게 조정
			// 캠과의 거리 구하기
			float toCamDis = FVector::Dist(camLoc, uiComp->GetComponentLocation());
			// GEngine->AddOnScreenDebugMessage(-1, -1.f, FColor::Green, FString::Printf(TEXT("거리 : %.2f"), toCamDis));
			// 크기 구하기
			float newScale = toCamDis / desireDis;
			// 크기 적용
			uiComp->SetWorldScale3D(FVector(newScale) * uiDefaultScale);
		}
	}
}
