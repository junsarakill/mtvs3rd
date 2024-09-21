// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JBS/BS_BillBoardWorldUIActor.h"
#include "BS_GrabHoverUIActor.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API ABS_GrabHoverUIActor : public ABS_BillBoardWorldUIActor
{
	GENERATED_BODY()
	
protected:
// 	hover ui 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Component")
	class UWidgetComponent* hoverUIComp;
// hover ui
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Component")
	// class UBS_ProfileUI* profileUI;	

	// 보임 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	bool isVisible = false;
		public:
	__declspec(property(get = GetIsVisible, put = SetIsVisible)) bool IS_VISIBLE;
	bool GetIsVisible()
	{
		return isVisible;
	}
	void SetIsVisible(bool value);
		protected:

public:

protected:
	virtual void BeginPlay() override;
public:

	virtual void Tick(float DeltaTime) override;

    void SetVisibleHoverUI(bool value);
};
