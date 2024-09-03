// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/SecondEventBoxActor.h"
#include "Components/StaticMeshComponent.h"


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
	
	// 15초 뒤에 사라진다
	SetLifeSpan(15);
	
	MeshComp->SetOwnerNoSee(true);
	MeshComp->SetOnlyOwnerSee(false);
}

// Called every frame
void ASecondEventBoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

