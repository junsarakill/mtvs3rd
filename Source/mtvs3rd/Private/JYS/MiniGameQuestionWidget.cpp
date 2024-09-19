// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/MiniGameQuestionWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include <JYS/MiniGameTriggerBox_Item.h>
#include "JYS/MiniGameWall.h"


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
	TArray<AActor*> outActor;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Table")), outActor);
	
	triggerBox = Cast<AMiniGameTriggerBox_Item>(outActor[0]);

}

void UMiniGameQuestionWidget::SetOwner(AQuestionsWidgetActor* actor)
{
	owner = actor;
}

void UMiniGameQuestionWidget::Onbtn_1Clicked()
{
	if (triggerBox->overlapActorTag == FName("shoes")) 
	{
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
		if (tag.Num() <= 0) return;

		AMiniGameWall* fadeOutWall = Cast<AMiniGameWall>(tag[0]);
		fadeOutWall->SetFadeOut();
	}
}

void UMiniGameQuestionWidget::Onbtn_2Clicked()
{
	if (triggerBox->overlapActorTag == FName("clothes")) 
	{
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
		if (tag.Num() <= 0) return;

		AMiniGameWall* fadeOutWall = Cast<AMiniGameWall>(tag[0]);
		fadeOutWall->SetFadeOut();
	}
}

void UMiniGameQuestionWidget::Onbtn_3Clicked()
{
	if (triggerBox->overlapActorTag == FName("hat")) 
	{
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
		if (tag.Num() <= 0) return;

		AMiniGameWall* fadeOutWall = Cast<AMiniGameWall>(tag[0]);
		fadeOutWall->SetFadeOut();
	}
}

void UMiniGameQuestionWidget::Onbtn_4Clicked()
{
	if (triggerBox->overlapActorTag == FName("bag")) 
	{
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
		if (tag.Num() <= 0) return;

		AMiniGameWall* fadeOutWall = Cast<AMiniGameWall>(tag[0]);
		fadeOutWall->SetFadeOut();
	}
}

void UMiniGameQuestionWidget::Onbtn_5Clicked()
{
	if (triggerBox->overlapActorTag == FName("Muffler")) 
	{
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
		if (tag.Num() <= 0) return;

		AMiniGameWall* fadeOutWall = Cast<AMiniGameWall>(tag[0]);
		fadeOutWall->SetFadeOut();
	}
}

void UMiniGameQuestionWidget::Onbtn_6Clicked()
{
	if (triggerBox->overlapActorTag == FName("watch")) 
	{
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("fadeOut"), tag);
		if (tag.Num() <= 0) return;

		AMiniGameWall* fadeOutWall = Cast<AMiniGameWall>(tag[0]);
		fadeOutWall->SetFadeOut();
	}
}
