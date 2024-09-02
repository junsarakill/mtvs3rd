// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_GrabbableActor.h"

// Sets default values
ABS_GrabbableActor::ABS_GrabbableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABS_GrabbableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABS_GrabbableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

