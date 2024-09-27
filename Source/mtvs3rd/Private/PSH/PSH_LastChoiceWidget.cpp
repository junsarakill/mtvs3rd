// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_LastChoiceWidget.h"
#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "Components/TextBlock.h"
#include "PSH/PSH_ChoiceResultWidget.h"
#include "Components/UniformGridPanel.h"
#include "mtvs3rd.h"
#include "Components/VerticalBox.h"

void UPSH_LastChoiceWidget::NativeConstruct()
{
	Super::NativeConstruct();	
	
}

void UPSH_LastChoiceWidget::SetData(FPSH_HttpDataTable data)
{
	WidgetData = data;
}
void UPSH_LastChoiceWidget::AddResult(const FString& ManName, const FString& WoManName)
{
	auto * ResultWidget = CreateWidget<UPSH_ChoiceResultWidget>(GetWorld(), ResultWdigetFactory);
	PRINTLOG(TEXT("ResultWidget == nullptr"));

	if(ResultWidget == nullptr) return;

	PRINTLOG(TEXT("ManName.IsEmpty() || WoManName.IsEmpty()"));
	if( ManName.IsEmpty() || WoManName.IsEmpty()) return;

	ResultWidget->Text_Man->SetText(FText::FromString(ManName)); //?
	ResultWidget->Text_Woman->SetText(FText::FromString(WoManName));

	VB_Result->AddChild(ResultWidget);
	PRINTLOG(TEXT("ResultWidget : %s"), *ResultWidget->GetName());
}