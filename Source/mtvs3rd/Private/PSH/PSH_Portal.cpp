// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_Portal.h"
#include "Components/WidgetComponent.h"
#include "PSH/PSH_PotalWidget.h"

// Sets default values
APSH_Portal::APSH_Portal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	widget->SetupAttachment(RootComponent);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APSH_Portal::BeginPlay()
{
	Super::BeginPlay();


	if (widget)
	{
		PotalWidget = Cast<UPSH_PotalWidget>(widget->GetWidget());
		if (PotalWidget)
		{
			PotalWidget->SetHttpACtor(this);
			UE_LOG(LogTemp, Warning, TEXT("HttpWidget : %s"), *PotalWidget->GetClass()->GetName());
		}
	}
}

// Called every frame
void APSH_Portal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

