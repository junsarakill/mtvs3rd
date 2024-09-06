// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_PotalWidget.h"
#include "PSH/PSH_Portal.h"
#include "Components/TextBlock.h"


void UPSH_PotalWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPSH_PotalWidget::SetPlayerCount()
{
	PlayerCount++;

	TB_PlayerCount->SetText(FText::FromString(FString::Printf(TEXT("Player : %d / %d"),PlayerCount , MaxPlayerCount)));

	if (PlayerCount >= MaxPlayerCount)
	{
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle,Actor,&APSH_Portal::GoPotal,2,false);
	}
}

void UPSH_PotalWidget::SetHttpACtor(class APSH_Portal* Owner)
{
	Actor = Owner;
}
 