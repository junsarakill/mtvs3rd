// Fill out your copyright notice in the Description page of Project Settings.

#include "JYS/MiniGameWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "JBS/BS_Utility.h"
#include "JBS/BS_VRPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "JBS/BS_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "JYS/MiniGameWall.h"
#include "PSH/PSH_HttpDataTable.h"
#include "JYS/MiniGameMissionWidget.h"
#include <JYS/MiniGameTriggerBox_Item.h>
#include "JYS/Countdown.h"
#include "Components/TextBlock.h"

// Sets default values
AMiniGameWidgetActor::AMiniGameWidgetActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    miniGameUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("miniGameUIComp"));
    miniGameUIComp->SetupAttachment(RootComponent);

    missionWidgetUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("missionWidgetUI"));
    missionWidgetUI->SetupAttachment(RootComponent);

    countDownWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("countDownWidget"));
    countDownWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMiniGameWidgetActor::BeginPlay()
{
    Super::BeginPlay();
    InitUI();
    auto* questionWidget = Cast<UMiniGameQuestionWidget>(miniGameUIComp->GetWidget());
    if (questionWidget)
    {
        questionWidget->SetOwner(this);
        questionWidget->owner = this;
    }
    ////// PC
    // pcWiidget = Cast<UQuestionsWidget>(CreateWidget(GetWorld(), pcWidgetFactory));
    // if (pcWiidget)
    //{
    //	pcWiidget->AddToViewport();
    //	pcWiidget->SetOwner(this);
    // }

    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" missionWidget"));
    // missionWidget = CreateWidget<UMiniGameMissionWidget>(GetWorld(), MissionWidgetFactory);
    if (missionWidgetUI)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" missionWidget1111111111"));

        missionWidgetUI->SetVisibility(true);
    }

	if (countDownWidget)
	{
		countDownWidget->SetVisibility(false);
	}

    FTimerHandle missionTimeHandle;
    GetWorldTimerManager().SetTimer(missionTimeHandle, this, &AMiniGameWidgetActor::HideMissionWidget, 10.0, false);

    //FTimerHandle handle;
    //GetWorldTimerManager().SetTimer(handle, this, &AMiniGameWidgetActor::CountDown, 1.0f, true, 0.0f);

	miniGameUIComp->SetVisibility(false);

    
    // Ʈ���Źڽ� ã��
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMiniGameTriggerBox_Item::StaticClass(), findTB);
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT(" %d"), findTB.Num()));


    BillBoardQuestionsWidget();
}

// Called every frame
void AMiniGameWidgetActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // BillBoardQuestionsWidget();

    float pre = 10000000;
    for (auto a : findTB)
    {
        if (this)
        {
            float distance = FVector::Dist(a->GetActorLocation(), this->GetActorLocation());
            if (pre > distance)
            {
                if (a)
                {
                    triggerBox = Cast<AMiniGameTriggerBox_Item>(a);
                }
            }
            pre = distance;
        }
    }

    auto countdownWidgetUI = Cast<UCountdown>(countDownWidget->GetWidget());
    countdownWidgetUI->seconds->SetText(FText::AsNumber(second));
    countdownWidgetUI->minute->SetText(FText::AsNumber(minutes));
}

void AMiniGameWidgetActor::BillBoardQuestionsWidget()
{
    // VR
    // �÷��̾� ī�޶� ��������
    auto *playerCam = Cast<ABS_VRPlayer>(this->GetOwner());
    if (playerCam->vrHMDCam)
    {
        FVector miniGameCamLoc = playerCam->vrHMDCam->GetComponentLocation();
        FVector camForwardVector = playerCam->vrHMDCam->GetForwardVector();

        // ������ ���ο� ��ġ ���� (ī�޶� �� 50cm ��ġ)
        FVector miniGameUILoc = miniGameCamLoc + camForwardVector * 300.0f;
        miniGameUIComp->SetWorldLocation(miniGameUILoc);
        missionWidgetUI->SetWorldLocation(miniGameUILoc);
        countDownWidget->SetWorldLocation(miniGameUILoc + FVector::UpVector * 50.f);

        // LookAt ������� ȸ�� ���
        FRotator lookRot = (miniGameCamLoc - miniGameUILoc).Rotation();

        // ������ ī�޶� �ٶ󺸰� ȸ�� (Pitch ���� �����Ͽ� ������ ��Ȯ�� ��������)
        miniGameUIComp->SetWorldRotation(lookRot + FRotator(0, 0, -0));
        missionWidgetUI->SetWorldRotation(lookRot + FRotator(0, 0, -0));
        countDownWidget->SetWorldRotation(lookRot + FRotator(0, 0, -0));
    }
}

void AMiniGameWidgetActor::InitUI() { bCheck = true; }

void AMiniGameWidgetActor::CountDown()
{
	//if (second != 0)
	//{
	//	second = second - 1;
	//}
    //else
    //{
    //    if (minutes == 0)
    //    {
    //        TArray<AActor *> OutActors;
    //        UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("FadeOut"), OutActors);
    //        auto *miniGameWall = Cast<AMiniGameWall>(OutActors[0]);
    //        if (miniGameWall)
    //        {
    //            miniGameWall->SetFadeOut();
    //        }
    //    }
    //    else
    //    {
    //        minutes = minutes - 1;
    //        second = 59;
    //    }
    //}
}

void AMiniGameWidgetActor::HideMissionWidget()
{
    if (missionWidget)
    {
        missionWidget->RemoveFromParent();
    }

    // JBS ���� �÷��̾� id�� ã�ƿ���
    auto* myPlayer = Cast<ABS_VRPlayer>(GetOwner());
    auto* ps = UBS_Utility::TryGetPlayerState(GetWorld(), myPlayer->ID);
    auto pd = ps->GetPlayerData();
    // /
    if (pd.Gender == "Man")
    {
        miniGameUIComp->SetVisibility(true);
        missionWidgetUI->SetVisibility(false);
    }
}
