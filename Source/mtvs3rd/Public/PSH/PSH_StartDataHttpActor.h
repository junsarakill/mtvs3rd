// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSH_HttpDataTable.h"
#include "PSH_StartDataHttpActor.generated.h"


UCLASS()
class MTVS3RD_API APSH_StartDataHttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APSH_StartDataHttpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HttpUiFact;

	UPROPERTY()
	class UPSH_StartDataWidget* httpUi;

	UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent * SelectComponent;

	UPROPERTY(EditDefaultsOnly)
	class TSubclassOf<UUserWidget> HttpWidgetFac;

	UPROPERTY(EditDefaultsOnly)
	class UPSH_StartDataWidget * HttpWidget;

	void SetVisible(bool chek);
	
};
