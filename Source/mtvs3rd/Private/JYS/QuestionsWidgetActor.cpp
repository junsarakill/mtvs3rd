// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/QuestionsWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "JYS/QuestionsWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "JBS/BS_VRPlayer.h"
#include "PSH/PSH_Mtvs3rdGameModBase.h"

// Sets default values
AQuestionsWidgetActor::AQuestionsWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// VR
 	questionsUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("questionsUI"));
 	questionsUIComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AQuestionsWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	////// PC
	//pcWiidget = Cast<UQuestionsWidget>(CreateWidget(GetWorld(), pcWidgetFactory));
	//if (pcWiidget)
	//{
	//	pcWiidget->AddToViewport();
	//	pcWiidget->SetOwner(this);
	//}
}

// Called every frame
void AQuestionsWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BillBoardQuestionsWidget();

	// playerCamera ������ player�� ī�޶�������Ʈ ��������
	auto* playerCamera = player->GetComponentByClass<UCameraComponent>();
	// spawnedWidgetActor(Widget UI)�� ������Ʈ�� �ٿ��ֱ�
	this->AttachToComponent(playerCamera, FAttachmentTransformRules::KeepRelativeTransform);
	// Widget UI Location ��ġ �������ֱ�
	FVector playerUILoc = playerCamera->GetForwardVector() * 1000;
	// this->SetActorRelativeLocation(playerUILoc);
}

void AQuestionsWidgetActor::BillBoardQuestionsWidget()
{
	if (auto* pc = GetWorld()->GetFirstPlayerController())
	{
		// VR
		// �÷��̾� ī�޶� ��������
		auto* cam = Cast<ABS_VRPlayer>(pc->GetCharacter());
 		if (cam->vrHMDCam)
 		{
			FVector camLoc = cam->vrHMDCam->GetComponentLocation();
			FVector camForwardVector = cam->vrHMDCam->GetForwardVector();

			// ������ ���ο� ��ġ ���� (ī�޶� �� 50cm ��ġ)
			FVector questionsUILoc = camLoc + camForwardVector * 800.0f;
			questionsUIComp->SetWorldLocation(questionsUILoc);

			// LookAt ������� ȸ�� ���
			FRotator lookRot = (camLoc - questionsUILoc).Rotation();

			// ������ ī�޶� �ٶ󺸰� ȸ�� (Pitch ���� �����Ͽ� ������ ��Ȯ�� ��������)
			questionsUIComp->SetWorldRotation(lookRot + FRotator(0, 0, -0));
			// questionsUIComp->SetRelativeLocation(camLoc + FVector());
	
 		}
	}
}

// ������ �̺�Ʈ ���° ������ Ŭ���ߴ����� ���� ����
void AQuestionsWidgetActor::SetAnswer(int num)
{
	answerNum = num;

	auto * GM = Cast<APSH_Mtvs3rdGameModBase>(GetWorld()->GetAuthGameMode());
	//GM->QestButtonJson(answerNum,); ���� ��ȣ ���� �ֱ�
	UE_LOG(LogTemp,Warning,TEXT("%d"),answerNum);
}

void AQuestionsWidgetActor::InitUI(int32 widgetNum)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("num : %d"),widgetNum ));
	switch (widgetNum)
	{
	case 1:
		questionsUIComp->SetWidgetClass(QuestionWidgetFactory1);
		break;
	case 2:
		questionsUIComp->SetWidgetClass(QuestionWidgetFactory2);
		break;
	}

	// VR
	UQuestionsWidget* widgetInstance = CastChecked<UQuestionsWidget>(questionsUIComp->GetWidget());
	widgetInstance->SetOwner(this);

	// widgetInstance->AddToViewport(0);

}
