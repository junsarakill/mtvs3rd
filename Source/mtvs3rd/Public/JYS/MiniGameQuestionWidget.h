// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniGameQuestionWidget.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UMiniGameQuestionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public: 

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_3;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_4;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestionBtn;

private: 

	UFUNCTION()
	void Onbtn_1Clicked();

	UFUNCTION()
	void Onbtn_2Clicked();

	UFUNCTION()
	void Onbtn_3Clicked();

	UFUNCTION()
	void Onbtn_4Clicked();
};
