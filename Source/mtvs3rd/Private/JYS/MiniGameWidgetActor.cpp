// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/MiniGameWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "JBS/BS_VRPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "JBS/BS_PlayerState.h"


// Sets default values
AMiniGameWidgetActor::AMiniGameWidgetActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	miniGameUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("miniGameUIComp"));
	miniGameUIComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMiniGameWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	InitUI();
	////// PC
	//pcWiidget = Cast<UQuestionsWidget>(CreateWidget(GetWorld(), pcWidgetFactory));
	//if (pcWiidget)
	//{
	//	pcWiidget->AddToViewport();
	//	pcWiidget->SetOwner(this);
	//}
}

// Called every frame
void AMiniGameWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BillBoardQuestionsWidget();

	destroyTime -= DeltaTime;
	if (destroyTime <= 0.0f)
	{

	}
}

void AMiniGameWidgetActor::BillBoardQuestionsWidget()
{
	// VR
	// �÷��̾� ī�޶� ��������
	auto* playerCam = Cast<ABS_VRPlayer>(this->GetOwner());
	if (playerCam->vrHMDCam)
	{
		FVector miniGameCamLoc = playerCam->vrHMDCam->GetComponentLocation();
		FVector camForwardVector = playerCam->vrHMDCam->GetForwardVector();

		// ������ ���ο� ��ġ ���� (ī�޶� �� 50cm ��ġ)
		FVector miniGameUILoc = miniGameCamLoc + camForwardVector * 800.0f;
		miniGameUIComp->SetWorldLocation(miniGameUILoc);

		// LookAt ������� ȸ�� ���
		FRotator lookRot = (miniGameCamLoc - miniGameUILoc).Rotation();

		// ������ ī�޶� �ٶ󺸰� ȸ�� (Pitch ���� �����Ͽ� ������ ��Ȯ�� ��������)
		miniGameUIComp->SetWorldRotation(lookRot + FRotator(0, 0, -0));
	}
}

void AMiniGameWidgetActor::InitUI()
{
	bCheck = true;

}