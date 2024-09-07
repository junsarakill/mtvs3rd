// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_StartDataHttpActor.h"
#include "Components/WidgetComponent.h"
#include "PSH/PSH_StartDataWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PSH_TsetJsonParseLib.h"
#include "HttpModule.h"
#include "PSH/PSH_Mtvs3rdGameModBase.h"

// Sets default values
APSH_StartDataHttpActor::APSH_StartDataHttpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//vr 모드
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
		
// 	httpUi = Cast<UPSH_StartDataWidget>(CreateWidget(GetWorld(), HttpUiFact));
// 	if (httpUi) // 테스트용
// 	{
// 		httpUi->AddToViewport();
// 		httpUi->SetHttpACtor(this);
// 		GetWorld()->GetAuthGameMode();
// 
// 		auto* pc = GetWorld()->GetFirstPlayerController();
// 		pc->SetShowMouseCursor(true);
// 		pc->SetInputMode(FInputModeUIOnly());
// 	}

	// vr전용
	if (SelectComponent)
	{
		HttpWidget = Cast<UPSH_StartDataWidget>(SelectComponent->GetWidget());
		if (HttpWidget)
		{
			HttpWidget->SetHttpACtor(this);
			UE_LOG(LogTemp, Warning, TEXT("HttpWidget : %s"), *HttpWidget->GetClass()->GetName());
		}
	}
	

}

// Called every frame
void APSH_StartDataHttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APSH_StartDataHttpActor::SetVisible(bool chek)
{
	
}

