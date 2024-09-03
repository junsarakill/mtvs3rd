// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "SecondEventTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API ASecondEventTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	ASecondEventTriggerBox();

protected:

	virtual void BeginPlay() override;

	// ������
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

public:

	// Box�� �÷��̾� ī�޶� ��ġ
	UPROPERTY(EditAnywhere, Category = "Box")
	TSubclassOf<AActor> boxFactory;

	UPROPERTY(EditDefaultsOnly)
	TArray<AActor*> players;

private:
	void PlaceBoxInFrontOfCamera(ACharacter* PlayerCharacter);

	class ACharacter* GetRandomPlayerWithTag(FName Tag);

	bool Once = true;
};
