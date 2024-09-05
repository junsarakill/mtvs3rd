// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSH_TsetJsonParseLib.h"
#include "PSH_StartDataHttpActor.h"
#include "PSH_StartDataWidget.generated.h"

/**
 * 
 */

class UButton;

UCLASS()
class MTVS3RD_API UPSH_StartDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	class APSH_StartDataHttpActor* HttpActor;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher * SelectSwicher;

	//Swicher Button
	UPROPERTY(meta = (BindWidget)) UButton * BT_MBTI;
	UPROPERTY(meta = (BindWidget)) UButton * BT_Request;

	UPROPERTY(meta = (BindWidget)) UButton * BT_Age;

	//Gender Button
	UPROPERTY(meta = (BindWidget)) UButton * BT_Man;
	UPROPERTY(meta = (BindWidget)) UButton * BT_Girl;
	FString GenderText;

	// Age Button
	FString AgeText;
	UPROPERTY(meta = (BindWidget)) UButton * BT_0; 
	UPROPERTY(meta = (BindWidget)) UButton * BT_1;	
	UPROPERTY(meta = (BindWidget)) UButton * BT_2;
	UPROPERTY(meta = (BindWidget)) UButton * BT_3;	
	UPROPERTY(meta = (BindWidget)) UButton * BT_4;
	UPROPERTY(meta = (BindWidget)) UButton * BT_5; 
	UPROPERTY(meta = (BindWidget)) UButton * BT_6;	
	UPROPERTY(meta = (BindWidget)) UButton * BT_7;
	UPROPERTY(meta = (BindWidget)) UButton * BT_8;	
	UPROPERTY(meta = (BindWidget)) UButton * BT_9;
	UPROPERTY(meta = (BindWidget)) UButton* BT_Clear;
	UPROPERTY(meta = (BindWidget)) UButton* BT_Choose;
	UPROPERTY(meta = (BindWidget)) class UTextBlock * TB_Age;
	UPROPERTY(meta = (BindWidget)) class UTextBlock * TB_ChoseAge;

	// MBTI Button
	FString MBTIText;
	UPROPERTY(meta = (BindWidget)) class UTextBlock * TB_MBTI;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ISTJ;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ISFJ;
	UPROPERTY(meta = (BindWidget)) UButton* BT_INFJ;
	UPROPERTY(meta = (BindWidget)) UButton* BT_INTJ;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ISTP;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ISFP;
	UPROPERTY(meta = (BindWidget)) UButton* BT_INFP;
	UPROPERTY(meta = (BindWidget)) UButton* BT_INTP;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ESTP;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ESFP;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ENFP;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ENTP;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ESTJ;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ESFJ;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ENFJ;
	UPROPERTY(meta = (BindWidget)) UButton* BT_ENTJ;

	// BloodType Button
	FString BloodText;
	UPROPERTY(meta = (BindWidget)) class UTextBlock * TB_Blood;
	UPROPERTY(meta = (BindWidget)) UButton* BT_Blood;
	UPROPERTY(meta = (BindWidget)) UButton* BT_A;
	UPROPERTY(meta = (BindWidget)) UButton* BT_B;
	UPROPERTY(meta = (BindWidget)) UButton* BT_AB;
	UPROPERTY(meta = (BindWidget)) UButton* BT_O;

public:
	virtual void NativeConstruct() override;

	UFUNCTION() void OnClickRequest();

	// Age Button FUNCTION
	UFUNCTION() void OnClick0();
	UFUNCTION() void OnClick1();
	UFUNCTION() void OnClick2();
	UFUNCTION() void OnClick3();
	UFUNCTION() void OnClick4();
	UFUNCTION() void OnClick5();
	UFUNCTION() void OnClick6();
	UFUNCTION() void OnClick7();
	UFUNCTION() void OnClick8();
	UFUNCTION() void OnClick9();
	UFUNCTION() void OnClickClear();
	UFUNCTION() void OnClickChoose();

	//Swicher  Button FUNCTION
	UFUNCTION()	void OnClickMBTI();
	UFUNCTION()	void OnClickAge();
	UFUNCTION()	void OnClickMan();
	UFUNCTION()	void OnClickGirl();

	
	// MBTI Button FUNCTION
	UFUNCTION() void OnClickISTJ();
	UFUNCTION() void OnClickISFJ();
	UFUNCTION() void OnClickINFJ();
	UFUNCTION() void OnClickINTJ();
	UFUNCTION() void OnClickISTP();
	UFUNCTION() void OnClickISFP();
	UFUNCTION() void OnClickINFP();
	UFUNCTION() void OnClickINTP();
	UFUNCTION() void OnClickESTP();
	UFUNCTION() void OnClickESFP();
	UFUNCTION() void OnClickENFP();
	UFUNCTION() void OnClickENTP();
	UFUNCTION() void OnClickESTJ();
	UFUNCTION() void OnClickESFJ();
	UFUNCTION() void OnClickENFJ();
	UFUNCTION() void OnClickENTJ();
	
	// BloodType Button FUNCTION
	UFUNCTION() void OnClickBlood();
	UFUNCTION() void OnClickA();
	UFUNCTION() void OnClickB();
	UFUNCTION() void OnClickO();
	UFUNCTION() void OnClickAB();

	void SetHttpACtor(class APSH_StartDataHttpActor* Owner);

	//Swicher  Button FUNCTION
	void SwichSlot(int num);


private:
	FString SetName(FString Gender);

	FPSH_HttpDataTable data;
	UPROPERTY()
	class APSH_Mtvs3rdGameModBase* GM;
};
