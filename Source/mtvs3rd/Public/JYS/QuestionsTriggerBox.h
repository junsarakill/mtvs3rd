// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "QuestionsTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API AQuestionsTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	AQuestionsTriggerBox();

protected:

	virtual void BeginPlay() override;
	
	// ¿À¹ö·¦
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

public: 
	// À§Á¬ ½ºÆù
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class AActor> questionsWidgetFactory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UShapeComponent* shapeComp;
	
};
