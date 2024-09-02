// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/QuestionsWidget.h"
#include "Components/Button.h"

void UQuestionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button1)
	{
		Button1->OnClicked.AddDynamic(this, &UQuestionsWidget::OnButtonClicked);
	}
	if (Button2)
	{
		Button2->OnClicked.AddDynamic(this, &UQuestionsWidget::OnButtonClicked);
	}
	if (Button3)
	{
		Button3->OnClicked.AddDynamic(this, &UQuestionsWidget::OnButtonClicked);
	}
	if (Button4)
	{
		Button4->OnClicked.AddDynamic(this, &UQuestionsWidget::OnButtonClicked);
	}
}

void UQuestionsWidget::OnButtonClicked()
{
	if (owner)
	{
		owner->Destroy();
	}
}
