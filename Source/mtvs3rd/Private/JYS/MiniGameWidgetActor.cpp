// Fill out your copyright notice in the Description page of Project Settings.

#include "JYS/MiniGameWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "JBS/BS_VRPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "JBS/BS_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "JYS/MiniGameWall.h"
#include "PSH/PSH_HttpDataTable.h"
#include "JYS/MiniGameMissionWidget.h"

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
    auto* questionWidget = Cast<UMiniGameQuestionWidget>(miniGameUIComp->GetWidget());
    if (questionWidget)
    {
        questionWidget->SetOwner(this);
    }
    ////// PC
    // pcWiidget = Cast<UQuestionsWidget>(CreateWidget(GetWorld(), pcWidgetFactory));
    // if (pcWiidget)
    //{
    //	pcWiidget->AddToViewport();
    //	pcWiidget->SetOwner(this);
    // }

    missionWidget = CreateWidget<UMiniGameMissionWidget>(GetWorld(), MissionWidgetFactory);
    if (missionWidget)
    {
        missionWidget->SetVisibility(ESlateVisibility::Visible);
    }

    FTimerHandle missionTimeHandle;
    GetWorldTimerManager().SetTimer(missionTimeHandle, this, &AMiniGameWidgetActor::HideMissionWidget, 10.0, false);

    //FTimerHandle handle;
    //GetWorldTimerManager().SetTimer(handle, this, &AMiniGameWidgetActor::CountDown, 1.0f, true, 0.0f);

    miniGameUIComp->SetVisibility(false);
}

// Called every frame
void AMiniGameWidgetActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
   // BillBoardQuestionsWidget();
}

void AMiniGameWidgetActor::BillBoardQuestionsWidget()
{
    // VR
    // 플레이어 카메라 가져오기
    auto *playerCam = Cast<ABS_VRPlayer>(this->GetOwner());
    if (playerCam->vrHMDCam)
    {
        FVector miniGameCamLoc = playerCam->vrHMDCam->GetComponentLocation();
        FVector camForwardVector = playerCam->vrHMDCam->GetForwardVector();

        // 위젯의 새로운 위치 설정 (카메라 앞 50cm 위치)
        FVector miniGameUILoc = miniGameCamLoc + camForwardVector * 800.0f;
        miniGameUIComp->SetWorldLocation(miniGameUILoc);

        // LookAt 방식으로 회전 계산
        FRotator lookRot = (miniGameCamLoc - miniGameUILoc).Rotation();

        // 위젯을 카메라를 바라보게 회전 (Pitch 값을 조정하여 위젯을 정확히 정면으로)
        miniGameUIComp->SetWorldRotation(lookRot + FRotator(0, 0, -0));
    }
}

void AMiniGameWidgetActor::InitUI() { bCheck = true; }

void AMiniGameWidgetActor::CountDown()
{
    if (second != 0)
    {
        second = second - 1;
    }
    else
    {
        if (minutes == 0)
        {
            TArray<AActor *> OutActors;
            UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("FadeOut"), OutActors);
            auto *miniGameWall = Cast<AMiniGameWall>(OutActors[0]);
            if (miniGameWall)
            {
                miniGameWall->SetFadeOut();
            }
        }
        else
        {
            minutes = minutes - 1;
            second = 59;
        }
    }
}

void AMiniGameWidgetActor::HideMissionWidget()
{
    if (missionWidget)
    {
        missionWidget->RemoveFromParent();
    }

    FPSH_HttpDataTable pd = Cast<ABS_VRPlayer>(GetOwner())->DATA;

    if (pd.Gender == "Man")
    {
        miniGameUIComp->SetVisibility(true);
    }
}
