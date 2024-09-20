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

	// ù ��° Ʈ���� �ڽ� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* itemBox;

	// �� ��° Ʈ���� �ڽ� ������Ʈ

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FName overlapActorTag;

private:

	// �±װ� ������ Ȯ���ϴ� �Լ�
	void CheckTags(FName checkTag);

	AActor* CurrentActor;
};
 