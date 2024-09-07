// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_FinalSelectComponent.h"

// Sets default values for this component's properties
UBS_FinalSelectComponent::UBS_FinalSelectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBS_FinalSelectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// 주인 손 설정
	gameObject = CastChecked<ABS_Hand>(GetOwner());
	
}


// Called every frame
void UBS_FinalSelectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBS_FinalSelectComponent::TrySpawnSelectConfirmUI(int selectPlayerId)
{
	// 이미 있는지 확인
	if(selectConfirmUIActor) return false;

	// 최종 선택 인지 확인
	check(gameObject);
	// 플레이어 스테이트 가져오기
	auto* player = gameObject->ownerPlayer;
	check(player);
	auto* playerPS = player->PS;
	check(playerPS);
	// 최종 선택 확인
	bool isFinal = playerPS->IS_FINAL_SELECT;
	if(isFinal)
	{
		SpawnSelectConfirmUI(selectPlayerId);
	}

    return isFinal;
}

void UBS_FinalSelectComponent::SetCurSelPlayerId(int value)
{
	curSelectedPlayerId = value;
}

void UBS_FinalSelectComponent::SpawnSelectConfirmUI(int selectPlayerId)
{
	// ui 액터 위치 가져오기
	auto* spPos = gameObject->ownerPlayer->playerUIPos1;
	// 액터 스폰
	selectConfirmUIActor = GetWorld()->SpawnActor<ABS_SelectConfirmActor>(
		scUIActorPrefab, spPos->GetComponentLocation(), spPos->GetComponentRotation());
	// 위치에 붙이기
	selectConfirmUIActor->AttachToComponent(spPos, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	// 선택 플레이어 id 갱신
	CUR_SELECT_PLAYER_ID = selectPlayerId;
	// 대리자 설정
	auto* scUI = selectConfirmUIActor->SELECT_CONFIRM_UI;
	check(scUI);
	scUI->confirmDelegate.AddUObject(this, &UBS_FinalSelectComponent::OnClickSelect);
}

void UBS_FinalSelectComponent::OnClickSelect(bool value)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("선택함: %d"), value));

	// 선택 액터 제거
	selectConfirmUIActor->Destroy();
	selectConfirmUIActor = nullptr;

	// yes 눌렀을 경우 게임모드에 선택 보내기
	if(value)
	{
		SendPlayerFinalSelect();
	}
}

void UBS_FinalSelectComponent::SendPlayerFinalSelect()
{
	// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%s"), str));
	auto* gm = Cast<APSH_Mtvs3rdGameModBase>(GetWorld()->GetAuthGameMode());
	if(gm)
	{
		// @@ main 받고 작업 from, to 데이터 보내기
	}
}
