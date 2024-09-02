// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_StartDataWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "PSH_TsetJsonParseLib.h"
#include "PSH/PSH_HttpActor.h"
#include "PSH/PSH_StartDataHttpActor.h"

void UPSH_StartDataWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Age Button FUNCTION
	BT_0->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClick0);
	BT_1->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClick1);
	BT_2->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClick2);
	BT_3->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClick3);
	BT_4->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClick4);
	BT_5->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClick5);
	BT_6->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClick6);
	BT_7->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClick7);
	BT_8->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClick8);
	BT_9->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClick9);
	BT_Choose->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClickChoose);
	BT_Clear->OnClicked.AddDynamic(this,&UPSH_StartDataWidget::OnClickClear);

// 	//Swicher  Button FUNCTION
	BT_MBTI->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickMBTI);
	BT_Age->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickAge);
	BT_Request->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickRequest);
	

// 	//Gender Button FUNCTION
	BT_Man->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickMan);
	BT_Girl->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickGirl);

// 	// MBTI Button FUNCTION
	BT_ISTJ->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickISTJ);
	BT_ISFJ->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickISFJ);
	BT_INFJ->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickINFJ);
	BT_INTJ->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickINTJ);
	BT_ISTP->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickISTP);
	BT_ISFP->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickISFP);
	BT_INFP->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickINFP);
	BT_INTP->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickINTP);
	BT_ESTP->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickESTP);
	BT_ESFP->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickESFP);
	BT_ENFP->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickENFP);
	BT_ENTP->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickENTP);
	BT_ESTJ->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickESTJ);
	BT_ESFJ->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickESFJ);
	BT_ENFJ->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickENFJ);
	BT_ENTJ->OnClicked.AddDynamic(this, &UPSH_StartDataWidget::OnClickENTJ);
	
}

void UPSH_StartDataWidget::OnClickRequest()
{
	if (HttpActor)
	{
		HttpActor->SetStartData(GenderText,AgeText,MBTIText);
		UE_LOG(LogTemp, Warning, TEXT("GenderText : %s , AgeText : %s ,  MBTIText : %s"), *GenderText, *AgeText, *MBTIText);
	}
	
}

void UPSH_StartDataWidget::OnClick0()
{
	
	if (AgeText.Len() > 1)
	{
		return;
	}
	else
	{
		AgeText += "0";
		TB_Age->SetText(FText::FromString(AgeText));
	}
	
}

void UPSH_StartDataWidget::OnClick1()
{
	if (AgeText.Len() > 1)
	{
		return;
	}
	else
	{
		AgeText += "1";
		TB_Age->SetText(FText::FromString(AgeText));
	}
}

void UPSH_StartDataWidget::OnClick2()
{
	
	if (AgeText.Len() > 1)
	{
		return;
	}
	else
	{
		AgeText += "2";
		TB_Age->SetText(FText::FromString(AgeText));
	}
}

void UPSH_StartDataWidget::OnClick3()
{
	if (AgeText.Len() > 1)
	{
		return;
	}
	else
	{
		AgeText += "3";
		TB_Age->SetText(FText::FromString(AgeText));
	}
}

void UPSH_StartDataWidget::OnClick4()
{
	if (AgeText.Len() > 1)
	{
		return;
	}
	else
	{
		AgeText += "4";
		TB_Age->SetText(FText::FromString(AgeText));
	}
}

void UPSH_StartDataWidget::OnClick5()
{
	if (AgeText.Len() > 1)
	{
		return;
	}
	else
	{
		AgeText += "5";
		TB_Age->SetText(FText::FromString(AgeText));
	}
}

void UPSH_StartDataWidget::OnClick6()
{
	
	if (AgeText.Len() > 1)
	{
		return;
	}
	else
	{
		AgeText += "6";
		TB_Age->SetText(FText::FromString(AgeText));
	}
}

void UPSH_StartDataWidget::OnClick7()
{	
	if (AgeText.Len() > 1)
	{
		return;
	}
	else
	{
		AgeText += "7";
		TB_Age->SetText(FText::FromString(AgeText));
	}
}

void UPSH_StartDataWidget::OnClick8()
{
	
	if (AgeText.Len() > 1)
	{
		return;
	}
	else
	{
		AgeText += "8";
		TB_Age->SetText(FText::FromString(AgeText));
	}
}

void UPSH_StartDataWidget::OnClick9()
{
	if (AgeText.Len() > 1)
	{
		return;
	}
	else
	{
		AgeText += "9";
		TB_Age->SetText(FText::FromString(AgeText));
	}
}

void UPSH_StartDataWidget::OnClickClear()
{
	AgeText.RemoveAt(AgeText.Len()-1);
	
	TB_Age->SetText(FText::FromString(AgeText));
}


void UPSH_StartDataWidget::OnClickChoose()
{
	FString PrintString = "Age : " ;
	TB_ChoseAge->SetText(FText::FromString(PrintString+AgeText));
	SwichSlot(0);
}

//Swicher Button FUNCTION
void UPSH_StartDataWidget::OnClickMBTI()
{
	SwichSlot(2);
}

void UPSH_StartDataWidget::OnClickAge()
{
	SwichSlot(1);
}

//MBTI Button FUNCTION
void UPSH_StartDataWidget::OnClickMan()
{
	GenderText = "Man";
}

void UPSH_StartDataWidget::OnClickGirl()
{
	GenderText = "Woman";
}

void UPSH_StartDataWidget::OnClickISTJ()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ISTJ"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickISFJ()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ISFJ"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickINFJ()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("INFJ"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickINTJ()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("INTJ"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickISTP()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ISTP"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickISFP()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ISFP"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickINFP()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("INFP"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickINTP()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("INTP"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickESTP()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ESTP"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickESFP()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ESFP"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickENFP()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ENFP"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}	

void UPSH_StartDataWidget::OnClickENTP()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ENTP"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickESTJ()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ESTJ"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickESFJ()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ESFJ"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickENFJ()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ENFJ"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::OnClickENTJ()
{
	SwichSlot(0);
	FString PrintString = "MBTI : ";
	MBTIText = FString::Printf(TEXT("ENTJ"));
	TB_MBTI->SetText(FText::FromString(PrintString + MBTIText));
}

void UPSH_StartDataWidget::SetHttpACtor(class APSH_StartDataHttpActor* Owner)
{
	HttpActor = Owner;
}

void UPSH_StartDataWidget::SwichSlot(int num)
{
	SelectSwicher->SetActiveWidgetIndex(num);
}
