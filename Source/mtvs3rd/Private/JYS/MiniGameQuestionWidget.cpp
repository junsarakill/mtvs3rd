// Fill out your copyright notice in the Description page of Project Settings.

#include "JYS/MiniGameQuestionWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include <JYS/MiniGameTriggerBox_Item.h>
#include "JYS/MiniGameWall.h"
#include "JYS/MiniGameWidgetActor.h"

void UMiniGameQuestionWidget::NativeConstruct()
{
    if (btn_1)
    {
        btn_1->OnClicked.AddDynamic(this, &UMiniGameQuestionWidget::Onbtn_1Clicked);
    }
    if (btn_2)
    {
        btn_2->OnClicked.AddDynamic(this, &UMiniGameQuestionWidget::Onbtn_2Clicked);
    }
    if (btn_3)
    {
        btn_3->OnClicked.AddDynamic(this, &UMiniGameQuestionWidget::Onbtn_3Clicked);
    }
    if (btn_4)
    {
        btn_4->OnClicked.AddDynamic(this, &UMiniGameQuestionWidget::Onbtn_4Clicked);
    }
    if (btn_5)
    {
        btn_5->OnClicked.AddDynamic(this, &UMiniGameQuestionWidget::Onbtn_5Clicked);
    }
    if (btn_6)
    {
        btn_6->OnClicked.AddDynamic(this, &UMiniGameQuestionWidget::Onbtn_6Clicked);
    }

    // TriggerBox에 있는 Table가져오기
    TArray<AActor *> outActor;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Table")), outActor);

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), actor, findTB);
}

void UMiniGameQuestionWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    float pre = 10000000;
    for (auto a : findTB)
    {
        if (owner)
        {
            float distance = FVector::Dist(a->GetActorLocation(), owner->GetActorLocation());
            if (pre > distance)
            {
                triggerBox = Cast<AMiniGameTriggerBox_Item>(a);
            }
            pre = distance;
        }
    }
}

void UMiniGameQuestionWidget::SetOwner(AMiniGameWidgetActor *miniActor) { owner = miniActor; }

void UMiniGameQuestionWidget::Onbtn_1Clicked()
{
    if (nullptr == triggerBox)
    {
        return;
    }

    if (triggerBox->overlapActorTag == FName("Shoes"))
    {
        StartCountDown();

        UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
        if (tag.Num() <= 0)
            return;

        AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
        fadeOutWall->SetFadeOut();
    }
}

void UMiniGameQuestionWidget::Onbtn_2Clicked()
{
    if (nullptr == triggerBox)
    {
        return;
    }

    if (triggerBox->overlapActorTag == FName("Clothes"))
    {
        StartCountDown();
        UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
        if (tag.Num() <= 0)
            return;

        AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
        fadeOutWall->SetFadeOut();
    }
}

void UMiniGameQuestionWidget::Onbtn_3Clicked()
{
    if (nullptr == triggerBox)
    {
        return;
    }
    if (triggerBox->overlapActorTag == FName("Hat"))
    {
        StartCountDown();
        UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
        if (tag.Num() <= 0)
            return;

        AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
        fadeOutWall->SetFadeOut();
    }
}

void UMiniGameQuestionWidget::Onbtn_4Clicked()
{
    if (nullptr == triggerBox)
    {
        return;
    }
    if (triggerBox->overlapActorTag == FName("Bag"))
    {
        StartCountDown();
        UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
        if (tag.Num() <= 0)
            return;

        AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
        fadeOutWall->SetFadeOut();
    }
}

void UMiniGameQuestionWidget::Onbtn_5Clicked()
{
    if (nullptr == triggerBox)
    {
        return;
    }
    if (triggerBox->overlapActorTag == FName("Muffler"))
    {
        StartCountDown();
        UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
        if (tag.Num() <= 0)
            return;

        AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
        fadeOutWall->SetFadeOut();
    }
}

void UMiniGameQuestionWidget::Onbtn_6Clicked()
{
    if (nullptr == triggerBox)
    {
        return;
    }

    if (triggerBox->overlapActorTag == FName("Watch"))
    {
        StartCountDown();
        UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
        if (tag.Num() <= 0)
            return;

        AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
        fadeOutWall->SetFadeOut();
    }
}

void UMiniGameQuestionWidget::StartCountDown()
{
    if (owner)
    {
        owner->CountDown();
    }
}
