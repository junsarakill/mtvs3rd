// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSH_LikeSocreWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class MTVS3RD_API UPSH_LikeSocreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:	
	
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher  * LS_Switcher;

	UPROPERTY(meta = (BindWidget))
	UButton * LS_One_Btn1;
	UPROPERTY(meta = (BindWidget))
	UButton * LS_One_Btn2;
	UPROPERTY(meta = (BindWidget))
	UButton * LS_One_Btn3;
	UPROPERTY(meta = (BindWidget))
	UButton * LS_One_Btn4;
	UPROPERTY(meta = (BindWidget))
	UButton * LS_One_Btn5;


	UPROPERTY(meta = (BindWidget))
	UButton * LS_Two_Btn1;
	UPROPERTY(meta = (BindWidget))
	UButton * LS_Two_Btn2;
	UPROPERTY(meta = (BindWidget))
	UButton * LS_Two_Btn3;
	UPROPERTY(meta = (BindWidget))
	UButton * LS_Two_Btn4;
	UPROPERTY(meta = (BindWidget))
	UButton * LS_Two_Btn5;

	

	UFUNCTION()
	void OnClikScoreButton1();
	UFUNCTION()
	void OnClikScoreButton2();
	UFUNCTION()
	void OnClikScoreButton3();
	UFUNCTION()
	void OnClikScoreButton4();
	UFUNCTION()
	void OnClikScoreButton5();

	UFUNCTION()
	void OnClikScoreButtonTwo1();
	UFUNCTION()
	void OnClikScoreButtonTwo2();
	UFUNCTION()
	void OnClikScoreButtonTwo3();
	UFUNCTION()
	void OnClikScoreButtonTwo4();
	UFUNCTION()
	void OnClikScoreButtonTwo5();
	
	void SetLikeSocreOwner(class APSH_LikgeScoreActor * owner);

	void SetScore(int NewScore);
	int score;

	class APSH_LikgeScoreActor * Actor;

	// 클릭하면 바로 보낸다. 서버로 통신. 반환 받은 값은 
};
