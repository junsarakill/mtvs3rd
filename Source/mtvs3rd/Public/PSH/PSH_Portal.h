// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSH_Portal.generated.h"

UCLASS()
class MTVS3RD_API APSH_Portal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APSH_Portal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly,Category = Mesh)
	class UStaticMeshComponent * mesh;

	UPROPERTY(EditDefaultsOnly,Category = widget)
	class UWidgetComponent * widget;

	UPROPERTY()
	class UPSH_PotalWidget * PotalWidget;

};
