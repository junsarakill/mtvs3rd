// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/QuestionsWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "JYS/QuestionsWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "JBS/BS_VRPlayer.h"
#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "JBS/BS_PlayerState.h"

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
	auto* pc = GetWorld()->GetFirstPlayerController();
	player = Cast<ABS_VRPlayer>(pc->GetCharacter());
}

// Called every frame
void AQuestionsWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BillBoardQuestionsWidget();

	// playerCamera 변수에 player의 카메라컴포넌트 가져오기
	auto* playerCamera = player->GetComponentByClass<UCameraComponent>();
	// spawnedWidgetActor(Widget UI)를 컴포넌트에 붙여주기
	this->AttachToComponent(playerCamera, FAttachmentTransformRules::KeepRelativeTransform);
	// Widget UI Location 위치 설정해주기
	FVector playerUILoc = playerCamera->GetForwardVector() * 1000;
	// this->SetActorRelativeLocation(playerUILoc);
}

void AQuestionsWidgetActor::BillBoardQuestionsWidget()
{
	if (auto* pc = GetWorld()->GetFirstPlayerController())
	{
		// VR
		// 플레이어 카메라 가져오기
		auto* cam = Cast<ABS_VRPlayer>(pc->GetCharacter());
 		if (cam->vrHMDCam)
 		{
			FVector camLoc = cam->vrHMDCam->GetComponentLocation();
			FVector camForwardVector = cam->vrHMDCam->GetForwardVector();

			// 위젯의 새로운 위치 설정 (카메라 앞 50cm 위치)
			FVector questionsUILoc = camLoc + camForwardVector * 800.0f;
			questionsUIComp->SetWorldLocation(questionsUILoc);

			// LookAt 방식으로 회전 계산
			FRotator lookRot = (camLoc - questionsUILoc).Rotation();

			// 위젯을 카메라를 바라보게 회전 (Pitch 값을 조정하여 위젯을 정확히 정면으로)
			questionsUIComp->SetWorldRotation(lookRot + FRotator(0, 0, -0));
			// questionsUIComp->SetRelativeLocation(camLoc + FVector());
	
 		}
	}
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
	//if (questionsUIComp)
	//{
	//	FString questionsNum = questionsUIComp->GetName();
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Question: %s"), *questionsNum));

	//}

	// VR
	UQuestionsWidget* widgetInstance = CastChecked<UQuestionsWidget>(questionsUIComp->GetWidget());
	widgetInstance->SetOwner(this);

	getWidgetNum = widgetNum;
}

// 선택지 이벤트 몇번째 정답을 클릭했는지에 대한 관리
void AQuestionsWidgetActor::SetAnswer(int num)
{
	answerNum = num;

	auto* ps = player->GetPlayerState<ABS_PlayerState>();
	
	auto * GM = Cast<APSH_Mtvs3rdGameModBase>(GetWorld()->GetAuthGameMode());
	GM->QestButtonJson(answerNum, getWidgetNum, ps->GetPlayerData().Id);
	UE_LOG(LogTemp,Warning,TEXT("%d"),answerNum);
}
