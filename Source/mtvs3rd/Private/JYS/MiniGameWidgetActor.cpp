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

    player = Cast<ACharacter>(this->GetOwner());

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

	miniGameUIComp->SetVisibility(false);

    
    // 트리거박스 찾기
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMiniGameTriggerBox_Item::StaticClass(), findTB);
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT(" %d"), findTB.Num()));


    // BillBoardQuestionsWidget();
}

// Called every frame
void AMiniGameWidgetActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    BillBoardQuestionsWidget();

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
    // 플레이어 카메라 가져오기
    auto *playerCam = Cast<ABS_VRPlayer>(this->GetOwner());
    if (playerCam->vrHMDCam)
    {
        FVector miniGameCamLoc = playerCam->vrHMDCam->GetComponentLocation();
        FVector camForwardVector = playerCam->vrHMDCam->GetForwardVector();
        FVector camDownVector = playerCam->vrHMDCam->GetUpVector();


        // 위젯의 새로운 위치 설정 (카메라 앞 50cm 위치)
        FVector miniGameUILoc = miniGameCamLoc + camForwardVector * 400.0f+ camDownVector * -100.0f;
        miniGameUIComp->SetWorldLocation(miniGameUILoc);
        missionWidgetUI->SetWorldLocation(miniGameUILoc);
        countDownWidget->SetWorldLocation(miniGameUILoc + FVector::UpVector * 50.f);

        // LookAt 방식으로 회전 계산
        FRotator lookRot = (miniGameCamLoc - miniGameUILoc).Rotation();

        // 위젯을 카메라를 바라보게 회전 (Pitch 값을 조정하여 위젯을 정확히 정면으로)
        miniGameUIComp->SetWorldRotation(lookRot + FRotator(0, 0, -0));
        missionWidgetUI->SetWorldRotation(lookRot + FRotator(0, 0, -0));
        countDownWidget->SetWorldRotation(lookRot + FRotator(0, 0, -0));
    }
}

void AMiniGameWidgetActor::InitUI() { bCheck = true; }



void AMiniGameWidgetActor::HideMissionWidget()
{
    if (missionWidget)
    {
        missionWidget->RemoveFromParent();
    }
    if (player->IsLocallyControlled())
    {
        SRPC_SetVisibilityByGender();
        // // 플레이어 id로 찾아오기
        // auto* myPlayer = Cast<ABS_VRPlayer>(GetOwner());
        // auto* ps = UBS_Utility::TryGetPlayerState(GetWorld(), myPlayer->ID);
        // auto pd = ps->GetPlayerData();
        // missionWidgetUI->SetVisibility(false);
  
		// if (pd.Gender == "Man")
		// {
        //     miniGameUIComp->SetVisibility(true);
        // }

    }
}

void AMiniGameWidgetActor::SRPC_SetVisibilityByGender_Implementation()
{
    // 플레이어 id로 찾아오기
    auto* myPlayer = Cast<ABS_VRPlayer>(GetOwner());
    auto* ps = myPlayer->GetPlayerState<ABS_PlayerState>();
    auto pd = ps->GetPlayerData();

    MRPC_SetVisibilityByGender(pd);
}

void AMiniGameWidgetActor::MRPC_SetVisibilityByGender_Implementation(FPSH_HttpDataTable playerData)
{
    missionWidgetUI->SetVisibility(false);
  
    //if (playerData.Gender == "Man")
    //{
        miniGameUIComp->SetVisibility(true);
    //}
}
