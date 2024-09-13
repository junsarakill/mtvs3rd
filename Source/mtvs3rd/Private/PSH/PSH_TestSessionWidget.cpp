// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_TestSessionWidget.h"
#include "Components/Button.h"
#include "PSH/PSH_GameInstance.h"

void UPSH_TestSessionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
 	BT_Create->OnClicked.AddDynamic(this,&UPSH_TestSessionWidget::CreateSessionButtonClicked);
 	BT_Join->OnClicked.AddDynamic(this,&UPSH_TestSessionWidget::JoinSessionButtonClicked);
}

void UPSH_TestSessionWidget::CreateSessionButtonClicked()
{
	UPSH_GameInstance* GameInstance = Cast<UPSH_GameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->CreateGameSession();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Orange,
				FString::Printf(TEXT("Create"))
				);
		}
	}
}

void UPSH_TestSessionWidget::JoinSessionButtonClicked()
{
	UPSH_GameInstance* GameInstance = Cast<UPSH_GameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->FindOtherSession();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Orange,
				FString::Printf(TEXT("Join"))
			);
		}
	}
}
