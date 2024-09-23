// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_LastChoiceActor.h"
#include "Components/WidgetComponent.h"
#include "PSH/PSH_LastChoiceWidget.h"
#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "Net/UnrealNetwork.h"

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

	bReplicates = true;
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
            ChoiceWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (HasAuthority())
	{
		
		auto* Gm = Cast<APSH_Mtvs3rdGameModBase>(GetWorld()->GetAuthGameMode());
		Gm->SetActor(this);
	}
}


// Called every frame
void APSH_LastChoiceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APSH_LastChoiceActor::SetPlayerName(FString Name) 
{
    playerCount++;

    if (playerCount > 1)
    {
        SRPC_Visible();
	}
	UE_LOG(LogTemp,Warning,TEXT("Name : %s"),*Name);

	
	// 첫번째는 왼쪽 Text에
	// 두번째는 오른쪽 Text에
}

void APSH_LastChoiceActor::SRPC_Visible_Implementation()
{
	MRPC_Visible();
}

void APSH_LastChoiceActor::MRPC_Visible_Implementation() 
{
	ChoiceWidget->SetVisibility(ESlateVisibility::Visible);
}

void APSH_LastChoiceActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);


    DOREPLIFETIME(APSH_LastChoiceActor, playerCount);
}

