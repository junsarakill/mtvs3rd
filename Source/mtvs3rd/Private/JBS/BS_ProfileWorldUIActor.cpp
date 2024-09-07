// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_ProfileWorldUIActor.h"
#include <JBS/BS_ProfileUI.h>
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ABS_ProfileWorldUIActor::ABS_ProfileWorldUIActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABS_ProfileWorldUIActor::BeginPlay()
{
	Super::BeginPlay();
	
	//XXX 생성하는 hand에서 해줌
	// SetProfileUI();
}

// Called every frame
void ABS_ProfileWorldUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BillboardUI(profileUIComp);
}

// void ABS_ProfileWorldUIActor::BillboardUI()
// {
// 	if(!profileUIComp) return;

// 	auto* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
// 	if(pc)
// 	{
// 		//pc로 뭔가 하기
// 		auto cam = pc->PlayerCameraManager;
// 		if(cam)
// 		{
// 			FVector targetLoc = cam->GetCameraLocation();
// 			FVector worldUILoc = profileUIComp->GetComponentLocation();
			
// 			FRotator lookRot = (targetLoc - worldUILoc).Rotation();
// 			profileUIComp->SetWorldRotation(lookRot);
// 		}
// 	}
// }

void ABS_ProfileWorldUIActor::SetProfileUIValue(FProfileData profileData)
{
	check(profileUI);
	profileUI->SetName(profileData.name);
	profileUI->SetSyncPercent(profileData.syncPercent);
	profileUI->SetCapturePlayer(profileData.type);
}