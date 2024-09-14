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
	class UButton* btn_5;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_6;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestionBtn;

	void SetOwner(class AQuestionsWidgetActor* actor);

	TArray<class AActor*> tag;
private: 

	UFUNCTION()
	void Onbtn_1Clicked();

	UFUNCTION()
	void Onbtn_2Clicked();

	UFUNCTION()
	void Onbtn_3Clicked();

	UFUNCTION()
	void Onbtn_4Clicked();

	UFUNCTION()
	void Onbtn_5Clicked();

	UFUNCTION()
	void Onbtn_6Clicked();

	UPROPERTY(EditDefaultsOnly)
	class AQuestionsWidgetActor* owner;

	class AMiniGameTriggerBox_Item* triggerBox;
};
