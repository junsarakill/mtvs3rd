// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MiniGameTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API AMiniGameTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	AMiniGameTriggerBox();

protected:

	virtual void BeginPlay() override;

	// ������
	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	// Ʈ���� �ڽ� ���ο� �ִ� ���� ��
	int32 playerCount = 0;
	
	// ���� �ִ� ���� ��
	const int32 MAXPLAYERCOUNT = 1;

	//UPROPERTY()
	//class UBoxComponent* collisionComp;

};
