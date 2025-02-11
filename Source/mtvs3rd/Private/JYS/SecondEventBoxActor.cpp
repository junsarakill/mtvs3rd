﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/SecondEventBoxActor.h"
#include "Components/StaticMeshComponent.h"
#include "JBS/BS_VRPlayer.h"


// Sets default values
ASecondEventBoxActor::ASecondEventBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ASecondEventBoxActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 검은 박스가 7초만 스폰되어있게 
	SetLifeSpan(7);

	Cast<ABS_VRPlayer>(GetOwner())->StartTrip();

	MeshComp->SetOwnerNoSee(true);
	MeshComp->SetOnlyOwnerSee(false);
}

// Called every frame
void ASecondEventBoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

