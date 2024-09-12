// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/MiniGameQuestionWidget.h"
#include "Components/Button.h"

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
}

void UMiniGameQuestionWidget::Onbtn_1Clicked()
{
}

void UMiniGameQuestionWidget::Onbtn_2Clicked()
{
}

void UMiniGameQuestionWidget::Onbtn_3Clicked()
{
}

void UMiniGameQuestionWidget::Onbtn_4Clicked()
{
}
