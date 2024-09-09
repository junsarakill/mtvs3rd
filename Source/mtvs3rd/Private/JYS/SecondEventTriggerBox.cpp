// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/SecondEventTriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

ASecondEventTriggerBox::ASecondEventTriggerBox()
{
}

void ASecondEventTriggerBox::BeginPlay()
{
	OnActorBeginOverlap.AddDynamic(this, &ASecondEventTriggerBox::OnOverlapBegin);

}

void ASecondEventTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	
	if (Once) {
		if (OtherActor && OtherActor != this)
		{
			// JBS �߰� �÷��̾ ��Ҵ��� üũ
			if(!OtherActor->ActorHasTag(FName(TEXT("Player"))) || OtherActor->ActorHasTag(FName(TEXT("Dummy"))))
				return;

			// "Player" �±׸� ���� ĳ���� �� �������� �ϳ��� �����մϴ�.
			ACharacter* RandomPlayer = GetRandomPlayerWithTag(TEXT("Player"));
			if (RandomPlayer)
			{
				PlaceBoxInFrontOfCamera(RandomPlayer);
			}
		}
		/*FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		UE_LOG(LogTemp, Warning, TEXT("3333333333"));
		GetWorld()->SpawnActor<AActor>(BoxFactory, GetActorLocation(), GetActorRotation(), spawnParams);*/
		Once = false;
	}
}

ACharacter* ASecondEventTriggerBox::GetRandomPlayerWithTag(FName Tag)
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, players);
	// JBS �߰� ���� ����
	TArray<AActor*> realPlayers;
	for(AActor* player : players)
	{
		if(player->ActorHasTag(FName(TEXT("Dummy"))))
			continue;
		else
		{
			realPlayers.Add(player);
		}
	}
	// /
	if (realPlayers.Num() > 0)
	{
		int32 randomIndex = FMath::RandRange(0, realPlayers.Num() - 1);
		return Cast<ACharacter>(realPlayers[randomIndex]);
	}

	return nullptr;
}

void ASecondEventTriggerBox::PlaceBoxInFrontOfCamera(ACharacter* PlayerCharacter)
{
	if (!PlayerCharacter || !boxFactory)
	{
		return;
	}

	// ī�޶� ������Ʈ ã��
	UCameraComponent* CameraComponent = PlayerCharacter->FindComponentByClass<UCameraComponent>();
	if (!CameraComponent || !boxFactory)
	{
		UE_LOG(LogTemp, Warning, TEXT("4444444444"));

		return;
	}

	// ī�޶� �տ� �ڽ� ��ġ ���
	FVector cameraLoc = CameraComponent->GetComponentLocation();
	FRotator cameraRot = CameraComponent->GetComponentRotation();
	FVector boxLoc = cameraLoc + cameraRot.Vector() * 100.f;

	// �ڽ� ����
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	AActor* spawnedBox = GetWorld()->SpawnActor<AActor>(boxFactory, boxLoc, cameraRot, spawnParams);
	check(spawnedBox);
	if (spawnedBox)
	{
		// �ڽ��� �÷��̾����� ����
		spawnedBox->AttachToComponent(CameraComponent, FAttachmentTransformRules::KeepWorldTransform);
	}
}

