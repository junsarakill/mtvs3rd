// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSH_ChoiceResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UPSH_ChoiceResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Man;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Woman;


};
