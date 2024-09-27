// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_LastChoiceActor.h"
#include "Components/WidgetComponent.h"
#include "PSH/PSH_LastChoiceWidget.h"
#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "Net/UnrealNetwork.h"
#include "mtvs3rd.h"
#include "JBS/BS_VRPlayerController.h"

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

	auto* pc = Cast<ABS_VRPlayerController>(GetWorld()->GetFirstPlayerController());
	if (pc)
	{
		SetOwner(pc);
	}


	/*if(!HasAuthority())*/


	if (ChoiceWidgetComponent)
	{
		ChoiceWidget = Cast<UPSH_LastChoiceWidget>(ChoiceWidgetComponent->GetWidget());
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

void APSH_LastChoiceActor::SetPlayerName(const FString& ManName, const FString& WomanName) // ¼­¹ö
{
    playerCount++;

    if (playerCount > 1)
    {
		PRINTLOG(TEXT("ManName : %s , WomanName : %s"),*ManName,*WomanName);
		playerCount = 0;
		MRPC_Visible(ManName, WomanName);
	}
}

void APSH_LastChoiceActor::MRPC_Visible_Implementation(const FString& ManName, const FString& WomanName)
{
	PRINTLOG(TEXT("ChoiceWidget"));
	if(ChoiceWidget == nullptr) return;


	PRINTLOG(TEXT("MRPC_LastChoiceActor"));
	ChoiceWidget->AddResult(ManName, WomanName);
	
}

void APSH_LastChoiceActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const 
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);


    DOREPLIFETIME(APSH_LastChoiceActor, playerCount);
}

