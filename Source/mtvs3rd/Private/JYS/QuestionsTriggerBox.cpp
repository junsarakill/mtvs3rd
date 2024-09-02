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
	// ���� ���Ͱ� "Player"��� �±׸� ������ �ִٸ�
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		TArray<AActor*> OutActor;
		// �ʿ� �ִ� ��� �÷��̾� ã��
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), OutActor);

		// for���� ������ �÷��̾�� �ش� i���� Widget �־��ֱ�
		for (int32 i = 0; i < OutActor.Num(); i++)
		{
			// spawnedWidgetActor ������ questionsWidgetFactory Widget UI ��������
			AQuestionsWidgetActor* spawnedWidgetActor = GetWorld()->SpawnActor<AQuestionsWidgetActor>(questionsWidgetFactory);

			// spawnedWidgetActor�� �ִ� player�� ���� i���� �־��ش� (�ڷ����� �ٸ��� ������ Actor�� Cast �ؼ� Character�� �ٲ��ֱ�
			spawnedWidgetActor->player = Cast<ACharacter>(OutActor[i]);

			// player ������ spawnedWidgetActor�� �ִ� player ��������
			auto* player = spawnedWidgetActor->player;
			// playerCamera ������ player�� ī�޶�������Ʈ ��������
			auto* playerCamera = player->GetComponentByClass<UCameraComponent>();
			// spawnedWidgetActor(Widget UI)�� ������Ʈ�� �ٿ��ֱ�
			spawnedWidgetActor->AttachToComponent(playerCamera, FAttachmentTransformRules::KeepRelativeTransform);
			// Widget UI Location ��ġ �������ֱ�
			FVector playerUILoc = playerCamera->GetForwardVector() * 300;
			spawnedWidgetActor->SetActorRelativeLocation(playerUILoc);
		}
		// Ʈ���Źڽ��� Collision ���ֱ�
		shapeComp->SetCollisionProfileName(FName("NoCollision"));	
	}
}
