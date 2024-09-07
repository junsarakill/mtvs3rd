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
	if (chek)
	{
		TB_MName->SetVisibility(ESlateVisibility::HitTestInvisible);
		TB_FName->SetVisibility(ESlateVisibility::HitTestInvisible);
		TB_Result->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		TB_MName->SetVisibility(ESlateVisibility::Hidden);
		TB_FName->SetVisibility(ESlateVisibility::Hidden);
		TB_Result->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UPSH_LastChoiceWidget::SuccessChoice()
{
	
	TB_Result->SetText(FText::FromString(TEXT("매칭에 성공하였습니다.")));

	VisibleName(true);
}

void UPSH_LastChoiceWidget::FailChoice()
{
	TB_Result->SetText(FText::FromString(TEXT("매칭에 실패하였습니다.")));
	TB_Result->SetVisibility(ESlateVisibility::HitTestInvisible);
}
