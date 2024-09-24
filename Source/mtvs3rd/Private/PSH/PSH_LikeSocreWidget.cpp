// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_LikeSocreWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"


void UPSH_LikeSocreWidget::NativeConstruct()
{
	Super::NativeConstruct();
	LS_One_Btn1->OnClicked.AddDynamic(this,&UPSH_LikeSocreWidget::OnClikScoreButton1);
	LS_One_Btn2->OnClicked.AddDynamic(this,&UPSH_LikeSocreWidget::OnClikScoreButton2);
	LS_One_Btn3->OnClicked.AddDynamic(this,&UPSH_LikeSocreWidget::OnClikScoreButton3);
	LS_One_Btn4->OnClicked.AddDynamic(this,&UPSH_LikeSocreWidget::OnClikScoreButton4);
	LS_One_Btn5->OnClicked.AddDynamic(this,&UPSH_LikeSocreWidget::OnClikScoreButton5);


	LS_Two_Btn1->OnClicked.AddDynamic(this, &UPSH_LikeSocreWidget::OnClikScoreButtonTwo1);
	LS_Two_Btn2->OnClicked.AddDynamic(this, &UPSH_LikeSocreWidget::OnClikScoreButtonTwo2);
	LS_Two_Btn3->OnClicked.AddDynamic(this, &UPSH_LikeSocreWidget::OnClikScoreButtonTwo3);
	LS_Two_Btn4->OnClicked.AddDynamic(this, &UPSH_LikeSocreWidget::OnClikScoreButtonTwo4);
	LS_Two_Btn5->OnClicked.AddDynamic(this, &UPSH_LikeSocreWidget::OnClikScoreButtonTwo5);
}

void UPSH_LikeSocreWidget::OnClikScoreButton1()
{
	LS_Switcher->SetActiveWidgetIndex(1);
	SetScore(1);
}

void UPSH_LikeSocreWidget::OnClikScoreButton2()
{
	LS_Switcher->SetActiveWidgetIndex(1);
	SetScore(1);
}

void UPSH_LikeSocreWidget::OnClikScoreButton3()
{
	LS_Switcher->SetActiveWidgetIndex(1);
	SetScore(1);
}

void UPSH_LikeSocreWidget::OnClikScoreButton4()
{
	LS_Switcher->SetActiveWidgetIndex(1);
	SetScore(1);
}

void UPSH_LikeSocreWidget::OnClikScoreButton5()
{
	LS_Switcher->SetActiveWidgetIndex(1);
	SetScore(1);
}

void UPSH_LikeSocreWidget::OnClikScoreButtonTwo1()
{
	SetVisibility(ESlateVisibility::Hidden);
	SetScore(1);
}

void UPSH_LikeSocreWidget::OnClikScoreButtonTwo2()
{
	SetVisibility(ESlateVisibility::Hidden);
	SetScore(1);
}

void UPSH_LikeSocreWidget::OnClikScoreButtonTwo3()
{
	SetVisibility(ESlateVisibility::Hidden);
	SetScore(1);
}

void UPSH_LikeSocreWidget::OnClikScoreButtonTwo4()
{
	SetVisibility(ESlateVisibility::Hidden);
	SetScore(1);
}

void UPSH_LikeSocreWidget::OnClikScoreButtonTwo5()
{
	SetVisibility(ESlateVisibility::Hidden);
	SetScore(1);
}

void UPSH_LikeSocreWidget::SetLikeSocreOwner(class APSH_LikgeScoreActor* owner)
{
	Actor = owner;
}

void UPSH_LikeSocreWidget::SetScore(int NewScore)
{
	score = NewScore;
}

