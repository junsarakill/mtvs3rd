// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <PSH/PSH_HttpDataTable.h>
#include <JBS/BS_Utility.h>
#include <JBS/BS_BillBoardWorldUIActor.h>
#include "BS_ProfileWorldUIActor.generated.h"

UCLASS()
class MTVS3RD_API ABS_ProfileWorldUIActor : public ABS_BillBoardWorldUIActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABS_ProfileWorldUIActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
// 	프로필 ui 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Component")
	class UWidgetComponent* profileUIComp;
// 프로필 ui
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Component")
	class UBS_ProfileUI* profileUI;

public:

protected:
	

	// // 빌보드
	// void BillboardUI();

public:
	// ui 설정
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetProfileUI();

	// ui 내용 설정
	void SetProfileUIValue(FProfileData profileData);
};
