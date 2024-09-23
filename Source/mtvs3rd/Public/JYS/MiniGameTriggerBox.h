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

	// 오버랩
	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly)
	class AMiniGameWall* miniGameWallFade;

private:
	// 트리거 박스 내부에 있는 액터 수
	int32 playerCount = 0;
	
	// 허용된 최대 액터 수
	const int32 MAXPLAYERCOUNT = 2;

	//UPROPERTY()
	//class UBoxComponent* collisionComp;

};
