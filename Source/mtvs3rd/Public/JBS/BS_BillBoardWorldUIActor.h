// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BS_BillBoardWorldUIActor.generated.h"

UCLASS()
class MTVS3RD_API ABS_BillBoardWorldUIActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABS_BillBoardWorldUIActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:


public:

protected:
	// 빌보드
	void BillboardUI(class UWidgetComponent* uiComp);

public:

};
