// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/QuestionsWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "JYS/QuestionsWidget.h"

// Sets default values
AQuestionsWidgetActor::AQuestionsWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
//// VR
// 	questionsUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("questionsUI"));
// 	questionsUIComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AQuestionsWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	//// PC
	pcWiidget = Cast<UQuestionsWidget>(CreateWidget(GetWorld(), pcWidgetFactory));
	if (pcWiidget)
	{
		pcWiidget->AddToViewport();
		pcWiidget->SetOwner(this);
	}
//// VR
// 	UQuestionsWidget* widgetInstance = CastChecked<UQuestionsWidget>(questionsUIComp->GetWidget());
// 	widgetInstance->owner = this;
// 
// 	widgetInstance->AddToViewport(0);
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
		//// VR
		// �÷��̾� ī�޶� ��������
// 		if (pc->PlayerCameraManager)
// 		{
// 			// ���� ���ؼ� ����
// 			FVector camLoc = pc->PlayerCameraManager->GetCameraLocation();
// 			FVector questionsUILoc = questionsUIComp->GetComponentLocation();
// 		
// 			FRotator lookRot = (camLoc - questionsUILoc).Rotation();
// 			questionsUIComp->SetWorldRotation(lookRot);
// 		}
	}
}

// ������ �̺�Ʈ ���° ������ Ŭ���ߴ����� ���� ����
void AQuestionsWidgetActor::SetAnswer(int num)
{
	answerNum = num;

	UE_LOG(LogTemp,Warning,TEXT("%d"),answerNum);
}

