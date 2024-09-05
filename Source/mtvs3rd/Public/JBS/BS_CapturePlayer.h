// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BS_Utility.h"
#include "BS_CapturePlayer.generated.h"

USTRUCT(BlueprintType)
struct FCapturePlayer
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	EPlayerType type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	class USkeletalMesh* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	TSubclassOf<UAnimInstance> anim;
};

UCLASS()
class MTVS3RD_API ABS_CapturePlayer : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABS_CapturePlayer();
	
	// 플레이어 종류 별 메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	TMap<EPlayerType, FCapturePlayer> meshMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 메시와 애니메이션 설정
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetMesh(EPlayerType type);

};
