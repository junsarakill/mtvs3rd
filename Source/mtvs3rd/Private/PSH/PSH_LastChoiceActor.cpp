// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_LastChoiceActor.h"
#include "Components/WidgetComponent.h"
#include "PSH/PSH_LastChoiceWidget.h"

// Sets default values
APSH_LastChoiceActor::APSH_LastChoiceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChoiceWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("SelectUi"));
	ChoiceWidgetComponent->SetupAttachment(RootComponent);

	ConstructorHelpers::FClassFinder<UUserWidget> TempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/PSH/Blueprints/UI/BP_PSH_LastChoiceWidget.BP_PSH_LastChoiceWidget_C'"));

	if (TempWidget.Succeeded())
	{
		ChoiceWidgetComponent->SetWidgetClass(TempWidget.Class);
		ChoiceWidgetComponent->SetDrawSize(FVector2D(500, 500));
	}
}

// Called when the game starts or when spawned
void APSH_LastChoiceActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (ChoiceWidgetComponent)
	{
		ChoiceWidget = Cast<UPSH_LastChoiceWidget>(ChoiceWidgetComponent->GetWidget());
		if (ChoiceWidget)
		{
			ChoiceWidget->SetActor(this);
		}
	}
}

// Called every frame
void APSH_LastChoiceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

