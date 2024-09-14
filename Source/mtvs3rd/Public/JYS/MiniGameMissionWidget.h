// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniGameMissionWidget.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UMiniGameMissionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	void SetOwner(class AMiniGameWidgetActor* actor);

private:
	UPROPERTY(EditDefaultsOnly)
	class AMiniGameWidgetActor* owner;
};
