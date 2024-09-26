// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UQuestionsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public: 

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button1;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button2;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button3;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button4;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Question1;

	void SetOwner(class AQuestionsWidgetActor * actor);

private: 
	UFUNCTION()
	void OnButton1Clicked();
	
	UFUNCTION()
	void OnButton2Clicked();
	
	UFUNCTION()
	void OnButton3Clicked();

	UFUNCTION()
	void OnButton4Clicked();

	UPROPERTY(EditDefaultsOnly)
	class AQuestionsWidgetActor* owner;
};
