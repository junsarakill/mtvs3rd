// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_LastChoiceWidget.h"
#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "Components/TextBlock.h"

void UPSH_LastChoiceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GM = Cast<APSH_Mtvs3rdGameModBase>(GetWorld()->GetAuthGameMode());
	
	if (GM)
	{
		GM->SetLastWdiget(this);
	}

	VisibleName(false);

}

void UPSH_LastChoiceWidget::SetActor(class APSH_LastChoiceActor* Owner)
{
	Actor = Owner;
}

void UPSH_LastChoiceWidget::SetData(FPSH_HttpDataTable data)
{
	WidgetData = data;
}

void UPSH_LastChoiceWidget::VisibleName(bool chek)
{
	
	
}

void UPSH_LastChoiceWidget::SuccessChoice()
{
	
	
}

void UPSH_LastChoiceWidget::FailChoice()
{
	
}
