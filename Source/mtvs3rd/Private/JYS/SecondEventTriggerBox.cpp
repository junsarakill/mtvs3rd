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
			// JBS 추가 플레이어가 닿았는지 체크
			if(!OtherActor->ActorHasTag(FName(TEXT("Player"))) || OtherActor->ActorHasTag(FName(TEXT("Dummy"))))
				return;

			// "Player" 태그를 가진 캐릭터 중 무작위로 하나를 선택합니다.
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
	// JBS 추가 더미 제외
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

	// 카메라 컴포넌트 찾기
	UCameraComponent* CameraComponent = PlayerCharacter->FindComponentByClass<UCameraComponent>();
	if (!CameraComponent || !boxFactory)
	{
		UE_LOG(LogTemp, Warning, TEXT("4444444444"));

		return;
	}

	// 카메라 앞에 박스 위치 계산
	FVector cameraLoc = CameraComponent->GetComponentLocation();
	FRotator cameraRot = CameraComponent->GetComponentRotation();
	FVector boxLoc = cameraLoc + cameraRot.Vector() * 100.f;

	// 박스 스폰
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	AActor* spawnedBox = GetWorld()->SpawnActor<AActor>(boxFactory, boxLoc, cameraRot, spawnParams);
	check(spawnedBox);
	if (spawnedBox)
	{
		// 박스를 플레이어한테 부착
		spawnedBox->AttachToComponent(CameraComponent, FAttachmentTransformRules::KeepWorldTransform);
	}
}

