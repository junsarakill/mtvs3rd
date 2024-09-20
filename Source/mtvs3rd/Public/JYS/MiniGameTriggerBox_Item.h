// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MiniGameTriggerBox_Item.generated.h"

/**
 *
 */
UCLASS()
class MTVS3RD_API AMiniGameTriggerBox_Item : public ATriggerBox
{
	GENERATED_BODY()

public:
	AMiniGameTriggerBox_Item();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// 첫 번째 트리거 박스 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* itemBox;

	// 두 번째 트리거 박스 컴포넌트

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FName overlapActorTag;

private:

	// 태그가 같은지 확인하는 함수
	void CheckTags(FName checkTag);

	AActor* CurrentActor;
};
 