// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/MiniGameTriggerBox_Item.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "JYS/MiniGameWall.h"

AMiniGameTriggerBox_Item::AMiniGameTriggerBox_Item()
{
	PrimaryActorTick.bCanEverTick = true;

	itemBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	itemBox->SetupAttachment(RootComponent);
	itemBox->SetCollisionProfileName("OverlapAllDynamic");

	itemBox->OnComponentBeginOverlap.AddDynamic(this, &AMiniGameTriggerBox_Item::OnOverlapBegin);

}

void AMiniGameTriggerBox_Item::BeginPlay()
{
}

void AMiniGameTriggerBox_Item::Tick(float DeltaTime)
{

}

void AMiniGameTriggerBox_Item::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("CanGrab")))
	{
		CurrentActor = OtherActor;
		CheckTags();
	}
}


void AMiniGameTriggerBox_Item::CheckTags()
{
	overlapActorTag = CurrentActor->Tags[0];
}
