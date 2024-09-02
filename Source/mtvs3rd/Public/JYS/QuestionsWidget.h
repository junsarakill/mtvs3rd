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

	UPROPERTY(EditDefaultsOnly)
	class AActor* owner;

private: 
	UFUNCTION()
	void OnButtonClicked();
};
