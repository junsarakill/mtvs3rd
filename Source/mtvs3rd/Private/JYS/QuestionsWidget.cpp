// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/QuestionsWidget.h"
#include "Components/Button.h"
#include "JYS/QuestionsWidgetActor.h"

void UQuestionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button1)
	{
		Button1->OnClicked.AddDynamic(this, &UQuestionsWidget::OnButton1Clicked);
	}
	if (Button2)
	{
		Button2->OnClicked.AddDynamic(this, &UQuestionsWidget::OnButton2Clicked);
	}
	if (Button3)
	{
		Button3->OnClicked.AddDynamic(this, &UQuestionsWidget::OnButton3Clicked);
	}
	if (Button4)
	{
		Button4->OnClicked.AddDynamic(this, &UQuestionsWidget::OnButton4Clicked);
	}
}



// owner 함수로 관리
void UQuestionsWidget::SetOwner(AQuestionsWidgetActor* actor)
{
	owner = actor;
}



void UQuestionsWidget::OnButton1Clicked()
{
	// owner 인덱스 할당
	owner->SetAnswer(1);


	if (owner)
	{
		owner->Destroy();
		RemoveFromParent();
	}
	else 
	{
		RemoveFromParent();
	}
}

void UQuestionsWidget::OnButton2Clicked()
{

	// owner 인덱스 할당
	owner->SetAnswer(2);

	if (owner)
	{
		owner->Destroy();
		RemoveFromParent();
	}
	else
	{
		RemoveFromParent();
	}
}

void UQuestionsWidget::OnButton3Clicked()
{
	// owner 인덱스 할당
	owner->SetAnswer(3);

	if (owner)
	{
		owner->Destroy();
		RemoveFromParent();
	}
	else
	{
		RemoveFromParent();
	}
}

void UQuestionsWidget::OnButton4Clicked()
{
	// owner 인덱스 할당
	owner->SetAnswer(4);

	if (owner)
	{
		owner->Destroy();
		RemoveFromParent();
	}
	else
	{
		RemoveFromParent();
	}
}
