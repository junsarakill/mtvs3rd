// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_PotalWidget.h"
#include "PSH/PSH_Portal.h"
#include "Components/TextBlock.h"


void UPSH_PotalWidget::NativeConstruct()
{
	Super::NativeConstruct();
    TB_PlayerCount->SetText(FText::FromString(FString::Printf(TEXT("Player : %d / %d"), 0, MaxPlayerCount)));
}

void UPSH_PotalWidget::SetPlayerCount(int32 PlayerCount)
{

	TB_PlayerCount->SetText(FText::FromString(FString::Printf(TEXT("Player : %d / %d"),PlayerCount , MaxPlayerCount)));

	if (PlayerCount >= MaxPlayerCount)
	{
		FTimerHandle handle;
		if (Actor)
		{
			GetWorld()->GetTimerManager().SetTimer(handle,Actor,&APSH_Portal::GoPotal,2,false);
		}
	}
}

void UPSH_PotalWidget::SetHttpACtor(class APSH_Portal* Owner)
{
	Actor = Owner;
}
 