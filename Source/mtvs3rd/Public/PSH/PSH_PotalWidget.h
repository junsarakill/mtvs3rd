// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSH_PotalWidget.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UPSH_PotalWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHttpACtor(class APSH_Portal* Owner);

	virtual void NativeConstruct() override;

	UPROPERTY()
	class APSH_Portal * Actor;
	
};
