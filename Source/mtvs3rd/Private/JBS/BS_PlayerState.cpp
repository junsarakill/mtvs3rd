// Fill out your copyright notice in the Description page of Project Settings.


#include <JBS/BS_PlayerState.h>
#include "PSH/PSH_HttpDataTable.h"
#include <Net/UnrealNetwork.h>

ABS_PlayerState::ABS_PlayerState()
{
    // Replication 설정
    bReplicates = true; // 이 객체가 복제되도록 설정
    bAlwaysRelevant = true; // 항상 관련 있는 상태로 유지
}

void ABS_PlayerState::SetIsAlreadySelect(bool value)
{
    isAlreadySelect = value;
}

FPSH_HttpDataTable ABS_PlayerState::GetPlayerData()
{

    // 구조체 화 하고 return
    int& syncId1 = idOrderAry[0];
    int& syncId2 = idOrderAry[1];
    float sync1 = syncId1 != -1 ? syncMap[syncId1] : -1.f;
    float sync2 = syncId2 != -1 ? syncMap[syncId2] : -1.f;

    return FPSH_HttpDataTable(id, name, age, gender, mbti, blood, syncId1, sync1, syncId2, sync2);
}

void ABS_PlayerState::SetPlayerData(FPSH_HttpDataTable data) 
{
    // 데이터 설정
    id = data.Id;
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
