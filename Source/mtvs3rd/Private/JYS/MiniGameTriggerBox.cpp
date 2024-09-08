// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/MiniGameTriggerBox.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "JYS/MiniGameWall.h"

AMiniGameTriggerBox::AMiniGameTriggerBox()
{
	UBoxComponent* collisionComp = Cast<UBoxComponent>(GetCollisionComponent());
	if (collisionComp)
	{
		collisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
		// 필요에 따라 오버랩 설정
		// CollisionComp->SetGenerateOverlapEvents(true);
		collisionComp->OnComponentEndOverlap.AddDynamic(this, &AMiniGameTriggerBox::OnOverlapEnd);
	}
}

void AMiniGameTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(),AMiniGameWall::StaticClass(), FName(TEXT("FadeIn")), OutActors);

	miniGameWallFade = Cast<AMiniGameWall>(OutActors[0]);
}

void AMiniGameTriggerBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		ACharacter* player = Cast<ACharacter>(OtherActor);
		if (player)
		{
			playerCount++;
			if (playerCount >= MAXPLAYERCOUNT)
			{
				UBoxComponent* collisionComp = Cast<UBoxComponent>(GetCollisionComponent());
				collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
				
				miniGameWallFade->SetFadeIn();
			}
		}
	}
}
