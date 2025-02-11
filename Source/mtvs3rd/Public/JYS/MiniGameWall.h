﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiniGameWall.generated.h"

UCLASS()
class MTVS3RD_API AMiniGameWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMiniGameWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* boxComp;


	UFUNCTION(BlueprintImplementableEvent)
	void SetFadeIn();	
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetFadeOut();
};
