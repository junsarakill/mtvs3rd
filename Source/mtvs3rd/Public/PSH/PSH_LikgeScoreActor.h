// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HttpFwd.h"
#include "PSH_LikgeScoreActor.generated.h"

UCLASS()
class MTVS3RD_API APSH_LikgeScoreActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APSH_LikgeScoreActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;

public:	

	UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent * Widget;

	void LikeScoreButtonJson();
	void LikeScoreButtonReqPost(FString json, FString URL);
	void LikeScoreButtonOnResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	UPROPERTY(EditAnywhere)
	FString URLScore;
};
