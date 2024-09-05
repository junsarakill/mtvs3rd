// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BS_Utility.h"
#include "BS_ProfileUI.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UBS_ProfileUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// 이름
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|UI", meta = (BindWidget))
	class UTextBlock* NameText;
	// 싱크로율
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|UI", meta = (BindWidget))
	class UTextBlock* SyncPercentText;


public:
	// 이름 설정
	void SetName(FString value);
	// 싱크로율 설정
	void SetSyncPercent(int32 value);
	// 3d 모델링 설정
	// FIXME 아마 플레이어는 gender를 아니깐 바꿔야할듯?
	void SetCapturePlayer(EPlayerType type);


};
