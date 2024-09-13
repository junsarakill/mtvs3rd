// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PSH/PSH_HttpDataTable.h"
#include "BS_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API ABS_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
protected:
	// 플레이어 데이터
	// id
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	int id;
	// 이름
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	FString name;
	// 나이
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	int age;
	// 성별 : 남, 녀
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	FString gender;
	// mbti
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	FString mbti;
	// 혈액형
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	FString blood;
	// 상대 id, 호감도
	// otherUserID1 : syncPercentID1
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	TMap<int, float> syncMap;
	
	// 플레이어 데이터 구조체
	UPROPERTY(VisibleAnywhere, Category="Default|Values", BlueprintGetter=GetPlayerData, BlueprintSetter=SetPlayerData)
	FPSH_HttpDataTable playerData;

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
		protected:

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

};
