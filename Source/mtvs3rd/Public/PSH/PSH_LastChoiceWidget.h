// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSH_HttpDataTable.h"
#include "PSH_LastChoiceWidget.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UPSH_LastChoiceWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	void SetActor(class APSH_LastChoiceActor* Owner );

	void SetData(FPSH_HttpDataTable data);
	class APSH_LastChoiceActor * Actor;

	FPSH_HttpDataTable WidgetData;
	UPROPERTY()
	class APSH_Mtvs3rdGameModBase* GM;


};
