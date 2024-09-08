// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestionsWidget.h"
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

	// ºôº¸µå
	UFUNCTION()
	void BillBoardQuestionsWidget();

	////// PC
	//UPROPERTY(EditDefaultsOnly)
	//class TSubclassOf<class UUserWidget> pcWidgetFactory1;	
	//
	////// PC
	//UPROPERTY(EditDefaultsOnly)
	//class TSubclassOf<class UUserWidget> pcWidgetFactory2;

	////// PC
	//UPROPERTY()
	//class UQuestionsWidget* pcWiidget;

	// VR
	UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* questionsUIComp;

	UPROPERTY(EditDefaultsOnly)
	class ACharacter* player;

	int32 answerNum;

	void SetAnswer(int num);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuestionsWidget> QuestionWidgetFactory1;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuestionsWidget> QuestionWidgetFactory2;

	void InitUI(int32 widgetNum);

	int32 getWidgetNum;
};
