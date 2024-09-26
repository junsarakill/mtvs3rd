// Fill out your copyright notice in the Description page of Project Settings.

#include "JYS/MiniGameQuestionWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include <JYS/MiniGameTriggerBox_Item.h>
#include "JYS/MiniGameWall.h"
#include "JYS/MiniGameWidgetActor.h"
#include "Components/WidgetComponent.h"

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
	TArray<AActor*> outActor;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Table")), outActor);

}

void UMiniGameQuestionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UMiniGameQuestionWidget::SetOwner(AMiniGameWidgetActor* miniActor) { owner = miniActor; }

void UMiniGameQuestionWidget::Onbtn_1Clicked()
{

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" 5555555555555"));
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true, 0.0f);
	if (nullptr == owner->triggerBox)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" 6666666666"));

		return;
	}
	owner->triggerBox->Tags.Add(FName("Shoes"));
	// if (triggerBox->overlapActorTag == FName("Shoes"))
	//{
	//    StartCountDown();

	//    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
	//    if (tag.Num() <= 0)
	//        return;

	//    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
	//    fadeOutWall->SetFadeOut();
	//}
	owner->miniGameUIComp->SetVisibility(false);
	StartCountDown();
}

void UMiniGameQuestionWidget::Onbtn_2Clicked()
{
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true, 0.0f);

	if (nullptr == owner->triggerBox)
	{
		return;
	}
	owner->triggerBox->Tags.Add(FName("Clothes"));
	//if (triggerBox->overlapActorTag == FName("Clothes"))
	//{
	//    StartCountDown();
	//    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
	//    if (tag.Num() <= 0)
	//        return;

	//    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
	//    fadeOutWall->SetFadeOut();
	//}
	owner->miniGameUIComp->SetVisibility(false);
	StartCountDown();
}

void UMiniGameQuestionWidget::Onbtn_3Clicked()
{
	
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true, 0.0f);

	if (nullptr == owner->triggerBox)
	{
		return;
	}
	owner->triggerBox->Tags.Add(FName("Hat"));

	//if (triggerBox->overlapActorTag == FName("Hat"))
	//{
	//    StartCountDown();
	//    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
	//    if (tag.Num() <= 0)
	//        return;

	//    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
	//    fadeOutWall->SetFadeOut();
	//}
	owner->miniGameUIComp->SetVisibility(false);
	StartCountDown();
}

void UMiniGameQuestionWidget::Onbtn_4Clicked()
{
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true, 0.0f);

	if (nullptr == owner->triggerBox)
	{
		return;
	}
	owner->triggerBox->Tags.Add(FName("Bag"));

	//if (triggerBox->overlapActorTag == FName("Bag"))
	//{
	//    StartCountDown();
	//    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
	//    if (tag.Num() <= 0)
	//        return;

	//    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
	//    fadeOutWall->SetFadeOut();
	//}
	owner->miniGameUIComp->SetVisibility(false);
	StartCountDown();
}

void UMiniGameQuestionWidget::Onbtn_5Clicked()
{
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true, 0.0f);

	if (nullptr == owner->triggerBox)
	{
		return;
	}
	owner->triggerBox->Tags.Add(FName("Muffler"));

	//if (triggerBox->overlapActorTag == FName("Muffler"))
	//{
	//    StartCountDown();
	//    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
	//    if (tag.Num() <= 0)
	//        return;

	//    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
	//    fadeOutWall->SetFadeOut();
	//}
	owner->miniGameUIComp->SetVisibility(false);
	StartCountDown();
}

void UMiniGameQuestionWidget::Onbtn_6Clicked()
{
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UMiniGameQuestionWidget::StartCountDown, 1.0f, true, 0.0f);

	if (nullptr == owner->triggerBox)
	{
		return;
	}
	owner->triggerBox->Tags.Add(FName("Watch"));

	//if (triggerBox->overlapActorTag == FName("Watch"))
	//{
	//    StartCountDown();
	//    UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
	//    if (tag.Num() <= 0)
	//        return;

	//    AMiniGameWall *fadeOutWall = Cast<AMiniGameWall>(tag[0]);
	//    fadeOutWall->SetFadeOut();
	//}
	owner->miniGameUIComp->SetVisibility(false);
	StartCountDown();
}

void UMiniGameQuestionWidget::StartCountDown()
{
	owner->countDownWidget->SetVisibility(true);
	/*   if (owner)
	   {
		   owner->CountDown();
	   }*/

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("FadeIn: %d"), owner->second));
	if (owner->second != 0)
	{
		owner->second = owner->second - 1;
	}
	else
	{
		if (owner->second == 0)
		{
			TArray<AActor*> OutActors;
			UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("FadeOut"), OutActors);
			auto* miniGameWall = Cast<AMiniGameWall>(OutActors[0]);
			if (miniGameWall)
			{
				GetWorld()->GetTimerManager().ClearTimer(handle);
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" FadeOut~~~~"));
				miniGameWall->SetFadeOut();
				owner->Destroy();
			}
		}
		else
		{
			owner->minutes = owner->minutes - 1;
			owner->second = 59;
		}
	}
}
