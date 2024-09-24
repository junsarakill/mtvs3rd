// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <JBS/BS_Utility.h>
#include "BS_FinalSelectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTVS3RD_API UBS_FinalSelectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBS_FinalSelectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// 최종 선택 ui 액터 프리팹
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	TSubclassOf<class ABS_SelectConfirmActor> scUIActorPrefab;
	
	// ui 액터
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Objects")
	class ABS_SelectConfirmActor* selectConfirmUIActor;
		public:
	__declspec(property(get = GetConfirmUIActor, put = SetConfirmUIActor)) class ABS_SelectConfirmActor* SELECT_CONFIRM_UI_ACTOR;
	class ABS_SelectConfirmActor* GetConfirmUIActor()
	{
		return selectConfirmUIActor;
	}
	void SetConfirmUIActor(class ABS_SelectConfirmActor* value);
		protected:

	// 현재 선택한 플레이어 id
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	int curSelectedPlayerId = -1;
		public:
	__declspec(property(get = GetCurSelPlayerId, put = SetCurSelPlayerId)) int CUR_SELECT_PLAYER_ID;
	int GetCurSelPlayerId()
	{
		return curSelectedPlayerId;
	}
	void SetCurSelPlayerId(int value);
		protected:

public:
	// 주인
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Objects")
	class ABS_Hand* gameObject;

	

protected:
	// 최종 선택 ui 생성
	UFUNCTION(BlueprintCallable)
	void SpawnSelectConfirmUI(int selectPlayerId);

	// 선택 ui 선택했을때
	UFUNCTION(BlueprintCallable)
	void OnClickSelect(bool value);

	// 최종 선택을 게임모드에 넘기기
	void SendPlayerFinalSelect(int fromId, int toId);

	// 기본
	UFUNCTION(BlueprintCallable)
	void SendPlayerFinalSelect();

	// 최종 선택
	void SendPlayerFinalSelect(EFinalSelectType type);


public:
	UFUNCTION(BlueprintCallable)
	bool TrySpawnSelectConfirmUI(int selectPlayerId);

	

};
