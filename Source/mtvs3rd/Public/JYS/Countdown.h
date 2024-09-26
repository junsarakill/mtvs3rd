// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Countdown.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UCountdown : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(meta = (BindWidget))
    class UTextBlock * minute;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* seconds;

};
