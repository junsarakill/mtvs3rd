// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include "Blueprint/UserWidget.h"
#include "BS_SelectConfirmUI.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FConfirmDelegate, bool)

UCLASS()
class MTVS3RD_API UBS_SelectConfirmUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|UI", meta = (BindWidget))
	class UButton* YesButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|UI", meta = (BindWidget))
	class UButton* NoButton;

	// 최종 선택 대리자
	FConfirmDelegate confirmDelegate;
	

	virtual void NativeConstruct() override;

	// 버튼 클릭
	UFUNCTION(BlueprintCallable)
	void OnClickYesBtn();
	UFUNCTION(BlueprintCallable)
	void OnClickNoBtn();


		
	
};
