// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_SelectConfirmActor.h"
#include "JBS/BS_BillBoardWorldUIActor.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABS_SelectConfirmActor::ABS_SelectConfirmActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	uiComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("uiComp"));
	uiComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABS_SelectConfirmActor::BeginPlay()
{
	Super::BeginPlay();
	
	CacheConfirmUI();
}

// Called every frame
void ABS_SelectConfirmActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 빌보드
	BillboardUI(uiComp);
}

void ABS_SelectConfirmActor::SetConfirmUI(UBS_SelectConfirmUI *value)
{
	selectConfirmUI = value;
}
