// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PSH/PSH_HttpDataTable.h"
#include <Containers/Map.h>
#include "BS_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API ABS_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	// 플레이어 데이터
	// id
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	int id = -1;
	// 이름
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	FString name = TEXT("미설정");
	// 나이
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	int age = -1;
	// 성별 : 남, 녀
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	FString gender = TEXT("미설정");
	// mbti
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	FString mbti = TEXT("미설정");
	// 혈액형
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	FString blood = TEXT("미설정");
	// 상대 id, 호감도 맵
	// otherUserID1 : syncPercentID1
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	TMap<int, float> syncMap;
	// id 순서 배열
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	TArray<int> idOrderAry = {-1,-1};

	// 최종선택 시점 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	bool isFinalSelect = false;
		public:
	__declspec(property(get = GetIsFinalSelect, put = SetIsFinalSelect)) bool IS_FINAL_SELECT;
	bool GetIsFinalSelect()
	{
		return isFinalSelect;
	}
	void SetIsFinalSelect(bool value);

	// 최종선택 확정 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	bool isAlreadySelect = false;
		public:
	__declspec(property(get = GetIsAlreadySelect, put = SetIsAlreadySelect)) bool IS_ALREADY_SELECT;
	bool GetIsAlreadySelect()
	{
		return isAlreadySelect;
	}
	void SetIsAlreadySelect(bool value);
	
protected:

public:
	UFUNCTION(BlueprintGetter)
	FPSH_HttpDataTable GetPlayerData();
	UFUNCTION(BlueprintSetter)
	void SetPlayerData(FPSH_HttpDataTable data);

	// 싱크로 맵에 요소 추가 : id , 해당유저에 대한 싱크로율
	UFUNCTION(BlueprintCallable)
	void AddSyncMap(int userId, float value);
};
