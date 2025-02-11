// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_FinalSelectComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "JBS/BS_Utility.h"
#include "TimerManager.h"
#include <JBS/BS_Hand.h>
#include <JBS/BS_VRPlayer.h>
#include <JBS/BS_PlayerState.h>
#include <JBS/BS_SelectConfirmActor.h>
#include <JBS/BS_SelectConfirmUI.h>
#include <PSH/PSH_Mtvs3rdGameModBase.h>

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
	SpawnSelectConfirmUI(selectPlayerId);

	return true;
}

void UBS_FinalSelectComponent::SetConfirmUIActor(ABS_SelectConfirmActor *value)
{
	selectConfirmUIActor = value;

	// 주인 플레이어
	gameObject->ownerPlayer->selectConfirmUIActor = this->selectConfirmUIActor;
}

void UBS_FinalSelectComponent::SetCurSelPlayerId(int value) 
{
	curSelectedPlayerId = value;
}

void UBS_FinalSelectComponent::SpawnSelectConfirmUI(int selectPlayerId)
{
	// 주인 플레이어 가져오기
	auto* player = gameObject->ownerPlayer;
	// ui 액터 위치 가져오기
	auto* spPos = player->playerUIPos1;
	// 액터 스폰
	SELECT_CONFIRM_UI_ACTOR = GetWorld()->SpawnActor<ABS_SelectConfirmActor>(
		scUIActorPrefab, spPos->GetComponentLocation(), spPos->GetComponentRotation());
	// 위치에 붙이기
	SELECT_CONFIRM_UI_ACTOR->AttachToComponent(spPos, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	// 선택 플레이어 id 갱신
	CUR_SELECT_PLAYER_ID = selectPlayerId;
	// 대리자 설정
	auto* scUI = SELECT_CONFIRM_UI_ACTOR->SELECT_CONFIRM_UI;
	check(scUI);
	scUI->confirmDelegate.AddUObject(this, &UBS_FinalSelectComponent::OnClickSelect);
}

void UBS_FinalSelectComponent::OnClickSelect(bool value)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("선택함: %d"), value));

	// 선택 액터 제거
	SELECT_CONFIRM_UI_ACTOR->Destroy();
	SELECT_CONFIRM_UI_ACTOR = nullptr;

	// yes 눌렀을 경우 게임모드에 선택 보내기
	if(value)
	{
		// XXX 프로토용
		// SendPlayerFinalSelect(EFinalSelectType::DUMMY);
		SendPlayerFinalSelect(EFinalSelectType::NORMAL);
	}
}

void UBS_FinalSelectComponent::SendPlayerFinalSelect(int fromId, int toId)
{
	auto* gm = UBS_Utility::GetGM(GetWorld());
	if(gm)
	{
		// 선택 데이터 보내기
		gm->LastChoice(fromId, toId);
		check(gameObject);
		check(gameObject->ownerPlayer);
		// 주인 정보
		auto* ownerPS = gameObject->ownerPlayer->GetPlayerState<ABS_PlayerState>();
		// 선택 확정 하기
		ownerPS->IS_ALREADY_SELECT = true;

		FString debugWorldStr = FString::Printf(TEXT("최종 선택 : fromid: %d, toid: %d"), fromId, toId);
		DrawDebugString(GetWorld()
		, gameObject->GetActorLocation() + FVector3d(0,0,FMath::RandRange(0,10))
		, debugWorldStr, nullptr, FColor::Green, 5.f, true);
	}
}

void UBS_FinalSelectComponent::SendPlayerFinalSelect()
{
	// 주인 플레이어 id
	// int playerId = gameObject->ownerPlayer->ID;

	// SendPlayerFinalSelect(playerId, CUR_SELECT_PLAYER_ID);
}

void UBS_FinalSelectComponent::SendPlayerFinalSelect(EFinalSelectType type)
{
	switch (type)
	{
	case EFinalSelectType::DUMMY:
	{
		// SendPlayerFinalSelect();

		// 1.5초 후 더미도 선택 보내기
		// FTimerHandle timerHandle;
		// GetWorld()->GetTimerManager()
		// 	.SetTimer(timerHandle, [this]() mutable
		// {
		// 	//타이머에서 할 거
		// 	// 주인 플레이어 id
		// 	// int32 playerId = gameObject->ownerPlayer->ID;


		// 	// SendPlayerFinalSelect(CUR_SELECT_PLAYER_ID, playerId);
		// }, 1.5f, false);
		
		break;
	}
	case EFinalSelectType::NORMAL:
		SRPC_SendPlayerFinalSelect();
		break;
	}

}

void UBS_FinalSelectComponent::SRPC_TrySpawnSelectConfirmUI_Implementation(int selectPlayerId)
{
    check(gameObject);
    // 이미 있는지 확인
    if (gameObject->ownerPlayer->selectConfirmUIActor)
        return;

    // 플레이어 스테이트 가져오기
    auto *player = gameObject->ownerPlayer;
    check(player);
    auto *playerPS = player->GetPlayerState<ABS_PlayerState>();
    check(playerPS);
    // 최종 선택 시점 && 이미 선택했는지 확인
    bool canSpawn = playerPS->IS_FINAL_SELECT && !playerPS->IS_ALREADY_SELECT;
    if (canSpawn)
    {
		MRPC_TrySpawnSelectConfirmUI(selectPlayerId);
    }
}

void UBS_FinalSelectComponent::MRPC_TrySpawnSelectConfirmUI_Implementation(int selectPlayerId)
{
	TrySpawnSelectConfirmUI(selectPlayerId);
	// SpawnSelectConfirmUI(selectPlayerId);
}

void UBS_FinalSelectComponent::SRPC_SendPlayerFinalSelect_Implementation()
{
	// id 가져오기
	int fromId = gameObject->ownerPlayer->GetPlayerState<ABS_PlayerState>()->ID;
	int toId = CUR_SELECT_PLAYER_ID;

	SendPlayerFinalSelect(fromId, toId);
}

void UBS_FinalSelectComponent::MRPC_SendPlayerFinalSelect_Implementation()
{
	
}