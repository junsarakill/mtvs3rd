// Fill out your copyright notice in the Description page of Project Settings.


#include <JBS/BS_PlayerState.h>
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "JBS/BS_Utility.h"
#include "JBS/BS_VRPlayer.h"
#include "PSH/PSH_GameInstance.h"
#include "PSH/PSH_HttpDataTable.h"
#include <Net/UnrealNetwork.h>
#include "Kismet/GameplayStatics.h"

ABS_PlayerState::ABS_PlayerState()
{
    // Replication 설정
    bReplicates = true; // 이 객체가 복제되도록 설정
    bAlwaysRelevant = true; // 항상 관련 있는 상태로 유지
}

void ABS_PlayerState::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    
}

void ABS_PlayerState::BeginPlay()
{
    Super::BeginPlay();

    // 플레이어 데이터 가져오기
    auto* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if(pc && pc->IsLocalController() && this == pc->GetPlayerState<ABS_PlayerState>())
    {
        //pc로 뭔가 하기
        auto* gi = UBS_Utility::GetGI(GetWorld());
        // gi에서 플레이어 데이터 가져오기
        SetPlayerData(gi->GetStartData());

        APlayerCameraManager* cam = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
        cam->StartCameraFade(1, 0, 5, FColor::Black);

        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("이름 : %s"), *name));
        // // 플레이어 캐릭터에게 ps 설정하기
        // pc->GetPawn<ABS_VRPlayer>()->PS = this;
    }
}

void ABS_PlayerState::SetIsAlreadySelect(bool value)
{
    isAlreadySelect = value;
}

FPSH_HttpDataTable ABS_PlayerState::GetPlayerData()
{

    // 구조체 화 하고 return
    if(idOrderAry.Num() < 2)
    {
        idOrderAry = {-1,-1};
    }
    int& syncId1 = idOrderAry[0];
    int& syncId2 = idOrderAry[1];
    float sync1 = syncId1 != -1 ? syncMap[syncId1] : -1.f;
    float sync2 = syncId2 != -1 ? syncMap[syncId2] : -1.f;

    return FPSH_HttpDataTable(ID, name, age, gender, mbti, blood, syncId1, sync1, syncId2, sync2);
}

void ABS_PlayerState::SetPlayerData(FPSH_HttpDataTable data) 
{
    // 데이터 설정
    ID = data.Id;
    name = data.Name;
    age = data.Age;
    gender = data.Gender;
    mbti = data.MBTI;
    blood = data.Blood;
    
    SRPC_AddSyncMap(data.otherUserID1, data.syncPercentID1);
    SRPC_AddSyncMap(data.otherUserID2, data.syncPercentID2);

}

void ABS_PlayerState::SetIsFinalSelect(bool value)
{
    isFinalSelect = value;
}

void ABS_PlayerState::AddSyncMap(int userId, float value)
{
    // 키 없으면 추가
    if(!syncMap.Contains(userId))
        idOrderAry.Add(userId);

    // 값 갱신
    syncMap.Add(userId, value);
}

void ABS_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Replicated 변수를 추가
    DOREPLIFETIME(ABS_PlayerState, id);
    DOREPLIFETIME(ABS_PlayerState, name);
    DOREPLIFETIME(ABS_PlayerState, age);
    DOREPLIFETIME(ABS_PlayerState, gender);
    DOREPLIFETIME(ABS_PlayerState, mbti);
    DOREPLIFETIME(ABS_PlayerState, blood);
    // DOREPLIFETIME(ABS_PlayerState, syncMap);
    DOREPLIFETIME(ABS_PlayerState, idOrderAry);
    DOREPLIFETIME(ABS_PlayerState, isFinalSelect);
    DOREPLIFETIME(ABS_PlayerState, isAlreadySelect);
}

void ABS_PlayerState::SRPC_AddSyncMap_Implementation(int userId, float value) { MRPC_AddSyncMap(userId, value); }

void ABS_PlayerState::MRPC_AddSyncMap_Implementation(int userId, float value)
{
    AddSyncMap(userId, value);
}


void ABS_PlayerState::SetId(int value)
{
    id = value;
    // @@ 플레이어 찾아서 id 동기화
    auto* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if(pc && pc->IsLocalController())
    {
        //pc로 뭔가 하기
        auto* player = pc->GetPawn<ABS_VRPlayer>();
        player->ID = this->ID;

        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("id 설정 체크 == ps id : %d, player id : %d")
        , this->ID, player->ID));
    }
}
