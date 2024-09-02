// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/QuestionsWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "JYS/QuestionsWidget.h"

// Sets default values
AQuestionsWidgetActor::AQuestionsWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	questionsUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("questionsUI"));
	questionsUIComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AQuestionsWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	
	UQuestionsWidget* widgetInstance = CastChecked<UQuestionsWidget>(questionsUIComp->GetWidget());
	widgetInstance->owner = this;
}

// Called every frame
void AQuestionsWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BillBoardQuestionsWidget();
}

void AQuestionsWidgetActor::BillBoardQuestionsWidget()
{
	if (auto* pc = GetWorld()->GetFirstPlayerController())
	{
		// 플레이어 카메라 가져오기
		if (pc->PlayerCameraManager)
		{
			// 방향 구해서 적용
			FVector camLoc = pc->PlayerCameraManager->GetCameraLocation();
			FVector questionsUILoc = questionsUIComp->GetComponentLocation();
		
			FRotator lookRot = (camLoc - questionsUILoc).Rotation();
			questionsUIComp->SetWorldRotation(lookRot);
		}
	}
}

