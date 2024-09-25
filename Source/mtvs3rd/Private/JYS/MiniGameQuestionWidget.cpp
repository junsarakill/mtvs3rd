// Fill out your copyright notice in the Description page of Project Settings.

#include "JYS/MiniGameQuestionWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include <JYS/MiniGameTriggerBox_Item.h>
#include "JYS/MiniGameWall.h"
#include "JYS/MiniGameWidgetActor.h"

void UMiniGameQuestionWidget::NativeConstruct()
{
    //if (btn_1)
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
                if (triggerBox)
                {
					triggerBox = Cast<AMiniGameTriggerBox_Item>(a);
                    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("00000000") );

                }
            }
            pre = distance;
        }
    }
}

void UMiniGameQuestionWidget::SetOwner(AMiniGameWidgetActor *miniActor) { owner = miniActor; }

void UMiniGameQuestionWidget::Onbtn_1Clicked()
{

    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" 5555555555555"));
    FTimerHandle handle;
    GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true,
                                                0.0f);
    if (nullptr == triggerBox)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" 6666666666"));

        return;
    }
    triggerBox->Tags.Add(FName("Shoes"));
    // if (triggerBox->overlapActorTag == FName("Shoes"))
    //{
    //    StartCountDown();

    //    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
    //    if (tag.Num() <= 0)
    //        return;

    //    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
    //    fadeOutWall->SetFadeOut();
    //}
    owner->Destroy();
}

void UMiniGameQuestionWidget::Onbtn_2Clicked()
{
    FTimerHandle handle;
    GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true, 0.0f);

    if (nullptr == triggerBox)
    {
        return;
    }
    triggerBox->Tags.Add(FName("Clothes"));
    //if (triggerBox->overlapActorTag == FName("Clothes"))
    //{
    //    StartCountDown();
    //    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
    //    if (tag.Num() <= 0)
    //        return;

    //    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
    //    fadeOutWall->SetFadeOut();
    //}
    owner->Destroy();
}

void UMiniGameQuestionWidget::Onbtn_3Clicked()
{
    FTimerHandle handle;
    GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true, 0.0f);

    if (nullptr == triggerBox)
    {
        return;
    }
    triggerBox->Tags.Add(FName("Hat"));

    //if (triggerBox->overlapActorTag == FName("Hat"))
    //{
    //    StartCountDown();
    //    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
    //    if (tag.Num() <= 0)
    //        return;

    //    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
    //    fadeOutWall->SetFadeOut();
    //}
    owner->Destroy();
}

void UMiniGameQuestionWidget::Onbtn_4Clicked()
{
    FTimerHandle handle;
    GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true, 0.0f);

    if (nullptr == triggerBox)
    {
        return;
    }
    triggerBox->Tags.Add(FName("Bag"));

    //if (triggerBox->overlapActorTag == FName("Bag"))
    //{
    //    StartCountDown();
    //    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
    //    if (tag.Num() <= 0)
    //        return;

    //    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
    //    fadeOutWall->SetFadeOut();
    //}
    owner->Destroy();
}

void UMiniGameQuestionWidget::Onbtn_5Clicked()
{
    FTimerHandle handle;
    GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true, 0.0f);

    if (nullptr == triggerBox)
    {
        return;
    }
    triggerBox->Tags.Add(FName("Muffler"));

    //if (triggerBox->overlapActorTag == FName("Muffler"))
    //{
    //    StartCountDown();
    //    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
    //    if (tag.Num() <= 0)
    //        return;

    //    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
    //    fadeOutWall->SetFadeOut();
    //}
    owner->Destroy();
}

void UMiniGameQuestionWidget::Onbtn_6Clicked()
{
    FTimerHandle handle;
    GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true, 0.0f);

    if (nullptr == triggerBox)
    {
        return;
    }
    triggerBox->Tags.Add(FName("Watch"));

    //if (triggerBox->overlapActorTag == FName("Watch"))
    //{
    //    StartCountDown();
    //    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
    //    if (tag.Num() <= 0)
    //        return;

    //    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
    //    fadeOutWall->SetFadeOut();
    //}
    owner->Destroy();
}

void UMiniGameQuestionWidget::StartCountDown()
{
    if (owner)
    {
        owner->CountDown();
    }
}
