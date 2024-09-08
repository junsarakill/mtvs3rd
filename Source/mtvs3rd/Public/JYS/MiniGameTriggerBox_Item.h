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
	class UBoxComponent* itemBox1;

	// �� ��° Ʈ���� �ڽ� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* itemBox2;

	UFUNCTION()
	void OnOverlapBegin1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapBegin2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



private:

	// �±װ� ������ Ȯ���ϴ� �Լ�
	void CheckTags();

	AActor* CurrentActor1;
	AActor* CurrentActor2;

	TArray<AActor> tag1;
};
