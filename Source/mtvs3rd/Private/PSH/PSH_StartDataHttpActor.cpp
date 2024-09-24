// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_StartDataHttpActor.h"
#include "Components/WidgetComponent.h"
#include "PSH/PSH_StartDataWidget.h"
#include "Kismet/GameplayStatics.h"
#include "HttpModule.h"
#include "PSH/PSH_Mtvs3rdGameModBase.h"

// Sets default values
APSH_StartDataHttpActor::APSH_StartDataHttpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//vr ¸ðµå
	SelectComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("SelectUi"));
	SelectComponent->SetupAttachment(RootComponent);
	
	ConstructorHelpers::FClassFinder<UUserWidget> TempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/PSH/Blueprints/UI/WBP_PSH_StartDataWidget.WBP_PSH_StartDataWidget_C'"));

	if (TempWidget.Succeeded())
	{
		SelectComponent->SetWidgetClass(TempWidget.Class);
		SelectComponent->SetDrawSize(FVector2D(500,500));
	}
}

// Called when the game starts or when spawned
void APSH_StartDataHttpActor::BeginPlay()
{
	Super::BeginPlay();

	if (SelectComponent)
	{
		HttpWidget = Cast<UPSH_StartDataWidget>(SelectComponent->GetWidget());
		if (HttpWidget)
		{
			HttpWidget->SetHttpACtor(this);
		}
	}
	
}
