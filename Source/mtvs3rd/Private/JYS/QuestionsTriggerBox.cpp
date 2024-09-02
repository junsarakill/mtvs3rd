// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/QuestionsTriggerBox.h"
#include "JYS/QuestionsWidget.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"


AQuestionsTriggerBox::AQuestionsTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AQuestionsTriggerBox::OnOverlapBegin);
}

void AQuestionsTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	//QuestionsWidget = CreateDefaultSubobject<UQuestionsWidget>(TEXT("QuestionsWidget"));
} 

void AQuestionsTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("1111"));
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		SpawnedWidgetActor = GetWorld()->SpawnActor<AActor>(QuestionsWidgetFactory);
	}
}
