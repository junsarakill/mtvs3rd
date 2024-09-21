// Fill out your copyright notice in the Description page of Project Settings.


#include <JBS/BS_PlayerState.h>
#include "PSH/PSH_HttpDataTable.h"

void ABS_PlayerState::SetIsAlreadySelect(bool value)
{
    isAlreadySelect = value;
}

FPSH_HttpDataTable ABS_PlayerState::GetPlayerData()
{

    // 구조체 화 하고 return
    int& syncId1 = idOrderAry[0];
    int& syncId2 = idOrderAry[1];
    float sync1 = syncId1 ? syncMap[syncId1] : -1.f;
    float sync2 = syncId2 ? syncMap[syncId2] : -1.f;

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
    
    AddSyncMap(data.otherUserID1, data.syncPercentID1);
    AddSyncMap(data.otherUserID2, data.syncPercentID2);
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