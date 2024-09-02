// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestionsWidgetActor.generated.h"

UCLASS()
class MTVS3RD_API AQuestionsWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestionsWidgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BillBoardQuestionsWidget();

	UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* questionsUIComp;

	UPROPERTY(EditDefaultsOnly)
	class ACharacter* player;
};
