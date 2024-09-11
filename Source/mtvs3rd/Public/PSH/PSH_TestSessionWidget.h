// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSH_TestSessionWidget.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UPSH_TestSessionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void CreateSessionButtonClicked();

	UFUNCTION()
	void JoinSessionButtonClicked();

	

	UPROPERTY(Meta = (BindWidget))
	class UButton * BT_Create;

	UPROPERTY(Meta = (BindWidget))
	class UButton * BT_Join;

		

};
