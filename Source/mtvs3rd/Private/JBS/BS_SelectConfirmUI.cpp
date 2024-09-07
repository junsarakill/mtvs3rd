// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_SelectConfirmUI.h"
#include "Components/Button.h"

void UBS_SelectConfirmUI::NativeConstruct()
{
    Super::NativeConstruct();

    
    YesButton->OnClicked.AddDynamic(this, &UBS_SelectConfirmUI::OnClickYesBtn);
    NoButton->OnClicked.AddDynamic(this, &UBS_SelectConfirmUI::OnClickNoBtn);
}

void UBS_SelectConfirmUI::OnClickYesBtn()
{
    confirmDelegate.Broadcast(true);
}

void UBS_SelectConfirmUI::OnClickNoBtn()
{
    confirmDelegate.Broadcast(false);
}
