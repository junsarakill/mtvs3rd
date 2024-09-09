// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/MiniGameTriggerBox_Item.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "JYS/MiniGameWall.h"

AMiniGameTriggerBox_Item::AMiniGameTriggerBox_Item()
{
	PrimaryActorTick.bCanEverTick = true;

	itemBox1 = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox1"));
	itemBox1->SetupAttachment(RootComponent);
	itemBox1->SetCollisionProfileName("OverlapAllDynamic");

	itemBox2 = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox2"));
	itemBox2->SetupAttachment(RootComponent);
	itemBox2->SetCollisionProfileName("OverlapAllDynamic");

	itemBox1->OnComponentBeginOverlap.AddDynamic(this, &AMiniGameTriggerBox_Item::OnOverlapBegin1);
	itemBox2->OnComponentBeginOverlap.AddDynamic(this, &AMiniGameTriggerBox_Item::OnOverlapBegin2);

}

void AMiniGameTriggerBox_Item::BeginPlay()
{
}

void AMiniGameTriggerBox_Item::Tick(float DeltaTime)
{
}

void AMiniGameTriggerBox_Item::OnOverlapBegin1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CurrentActor1 = OtherActor;
	CheckTags();
}

void AMiniGameTriggerBox_Item::OnOverlapBegin2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CurrentActor2 = OtherActor;
	CheckTags();
}

void AMiniGameTriggerBox_Item::CheckTags()
{
	TArray<AActor*> tag;
	if(!CurrentActor1 || !CurrentActor2)
		return;
		
	if (CurrentActor1->Tags[1] == CurrentActor2->Tags[1])
	{
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
		if(tag.Num() <= 0) return;

		AMiniGameWall* fadeOutWall = Cast<AMiniGameWall>(tag[0]);
		fadeOutWall->SetFadeOut();
	}
}
