// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/QuestionsTriggerBox.h"
#include "JYS/QuestionsWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "JYS/QuestionsWidgetActor.h"
#include "Camera/CameraComponent.h"
#include "Components/ShapeComponent.h"


AQuestionsTriggerBox::AQuestionsTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AQuestionsTriggerBox::OnOverlapBegin);
}

void AQuestionsTriggerBox::BeginPlay()
{
	Super::BeginPlay();
} 

void AQuestionsTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("1111"));
	// 만약 맥터가 "Player"라는 태그를 가지고 있다면
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		TArray<AActor*> OutActor;
		// 맵에 있는 모든 플레이어 찾기
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), OutActor);

		// for문을 돌려서 플레이어에게 해당 i번의 Widget 넣어주기
		for (int32 i = 0; i < OutActor.Num(); i++)
		{
			// spawnedWidgetActor 변수에 questionsWidgetFactory Widget UI 가져오기
			AQuestionsWidgetActor* spawnedWidgetActor = GetWorld()->SpawnActor<AQuestionsWidgetActor>(questionsWidgetFactory);

			// spawnedWidgetActor에 있는 player에 액터 i번을 넣어준다 (자료형이 다르기 때문에 Actor를 Cast 해서 Character로 바꿔주기
			spawnedWidgetActor->player = Cast<ACharacter>(OutActor[i]);

			// player 변수에 spawnedWidgetActor에 있는 player 가져오기
			auto* player = spawnedWidgetActor->player;
			// playerCamera 변수에 player의 카메라컴포넌트 가져오기
			auto* playerCamera = player->GetComponentByClass<UCameraComponent>();
			// spawnedWidgetActor(Widget UI)를 컴포넌트에 붙여주기
			spawnedWidgetActor->AttachToComponent(playerCamera, FAttachmentTransformRules::KeepRelativeTransform);
			// Widget UI Location 위치 설정해주기
			FVector playerUILoc = playerCamera->GetForwardVector() * 300;
			spawnedWidgetActor->SetActorRelativeLocation(playerUILoc);
		}
		// 트리거박스의 Collision 꺼주기
		shapeComp->SetCollisionProfileName(FName("NoCollision"));	
	}
}
