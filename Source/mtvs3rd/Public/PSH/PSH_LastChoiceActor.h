// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSH_LastChoiceActor.generated.h"

UCLASS()
class MTVS3RD_API APSH_LastChoiceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APSH_LastChoiceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY()
	class UPSH_LastChoiceWidget* ChoiceWidget;
 
	UPROPERTY(EditDefaultsOnly)
 	class UWidgetComponent * ChoiceWidgetComponent;

	void SetPlayerName(const FString& ManName, const FString& WomanName);

	UPROPERTY(EditAnywhere,Replicated)
	int playerCount = 0;

	UFUNCTION(NetMulticast,Reliable)
	void MRPC_Visible(const FString& ManName, const FString& WomanName);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const;

};
