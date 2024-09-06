// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_Portal.h"
#include "Components/WidgetComponent.h"
#include "PSH/PSH_PotalWidget.h"
#include "JBS/BS_VRPlayer.h"
#include "mtvs3rdCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APSH_Portal::APSH_Portal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	widget->SetupAttachment(RootComponent);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APSH_Portal::BeginPlay()
{
	Super::BeginPlay();

	mesh->OnComponentBeginOverlap.AddDynamic(this, &APSH_Portal::OnComponentBeginOverlap);

	if (widget)
	{
		PotalWidget = Cast<UPSH_PotalWidget>(widget->GetWidget());
		if (PotalWidget)
		{
			PotalWidget->SetHttpACtor(this);
			UE_LOG(LogTemp, Warning, TEXT("HttpWidget : %s"), *PotalWidget->GetClass()->GetName());
		}
	}

	SetPortal();

	if (bisEndPotal)
	{
		mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		widget->SetVisibility(false);
	}
}

// Called every frame
void APSH_Portal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APSH_Portal::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ABS_VRPlayer * player = Cast<ABS_VRPlayer>(OtherActor);
	player = Cast<Amtvs3rdCharacter>(OtherActor);
	if (player)
	{
		 // 플레이어가 부딫히면 카운트를 올림
		 PotalWidget->SetPlayerCount();
		 // 올리고 콜리전을 끔.
		Setvisilbe(false);
	}
}

void APSH_Portal::Setvisilbe(bool chek)
{
	//mesh->SetVisibility(chek);
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APSH_Portal::SetPortal()
{
	FName nam = TagetName;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), nam,EndPotal);
}

void APSH_Portal::GoPotal()
{
	if (player)
	{
		player->SetActorLocation(EndPotal[0]->GetActorLocation());
	}
}

