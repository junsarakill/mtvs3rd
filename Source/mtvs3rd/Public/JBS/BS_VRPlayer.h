// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include "GameFramework/Character.h"
#include <PSH/PSH_HttpDataTable.h>
#include <JBS/BS_Utility.h>
#include "BS_VRPlayer.generated.h"

UCLASS()
class MTVS3RD_API ABS_VRPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABS_VRPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region 변수 영역
protected:
	// 플레이어 id
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	int id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	float cameraHeight = 166.f;
	// 이동 속도
	// @@ 트리거 세기에 따라 이동속도 조절되면 좋을듯?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values", BlueprintGetter=GetMoveSpeed, BlueprintSetter=SetMoveSpeed)
	float moveSpeed = 600.f;
		public:
	__declspec(property(get = GetMoveSpeed, put = SetMoveSpeed)) float MOVE_SPEED;
	UFUNCTION(BlueprintGetter)
	float GetMoveSpeed()
	{
		return moveSpeed;
	}
	UFUNCTION(BlueprintSetter)
	void SetMoveSpeed(float value);
		protected:

	// 이동 방향
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	FVector moveDir;

	// 회전 설정
	// @@ 나중엔 자연스러운 회전 추가할까?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	bool isSnapTurn = true;

	// 스냅턴 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	float snapTurnDeg = 45.f;

	// 회전 배율
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	float smoothTurnMulti = 5.f;

	// XXX 디버그용 최종 선택 가능
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Debug")
	bool enableDebugFinalSelect = false;

	// pc 모드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Debug")
	bool playOnPC = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Debug")
	bool enableViewPlayerStat = true;

	// 플레이어 데이터
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	FPSH_HttpDataTable data;
		public:
	__declspec(property(get = GetPlayerData, put = SetPlayerData)) FPSH_HttpDataTable DATA;
	FPSH_HttpDataTable GetPlayerData();
	
    protected:

	

#pragma region 프리팹

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	class UInputMappingContext* imcDefault;

	// 플레이어 외형 데이터 맵
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	TMap<EPlayerType, FPlayerAppearanceData> playerAppearanceMap;
	

#pragma endregion

#pragma region 컴포넌트, 오브젝트
	// 플레이어 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Objects")
	class ABS_PlayerState* ps;
		public:
	__declspec(property(get = GetPS, put = SetPS)) ABS_PlayerState* PS;
        ABS_PlayerState *GetPS();
        void SetPS(ABS_PlayerState* value);
		protected:

	// 애니메이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Components", BlueprintGetter=GetAnim, BlueprintSetter=SetAnim)
	class UBS_PlayerBaseAnimInstance* anim;
		public:
	__declspec(property(get = GetAnim, put = SetAnim)) class UBS_PlayerBaseAnimInstance* ANIM;
	UFUNCTION(BlueprintGetter)
	class UBS_PlayerBaseAnimInstance *GetAnim();
	UFUNCTION(BlueprintSetter)
	void SetAnim(class UBS_PlayerBaseAnimInstance* value)
	{
		anim = value;
	}
		protected:

public:
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class USceneComponent* vrRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class UCameraComponent* vrHMDCam;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class ABS_Hand* leftController;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class ABS_Hand* rightController;
	// 최종 선택 UI 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Component")
	class UStaticMeshComponent* playerUIPos1;

	// 최종 선택 ui 액터
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Objects")
	class ABS_SelectConfirmActor* selectConfirmUIActor;

	
	
#pragma endregion
#pragma endregion
#pragma region 함수 영역
protected:
	// 이동방향 설정
	UFUNCTION(BlueprintCallable)
	void EventMove(FVector2D dir);

	// 썸스틱으로 회전
	UFUNCTION(BlueprintCallable)
	void EventTurn(float value);

	void SnapTurn(bool isRight);

	//자연스러운 회전
	void SmoothTurn(float value);

	// 마우스 회전
	UFUNCTION(BlueprintCallable)
	void EventLookup(FVector2D value);

	// 플레이어 id 설정하기
	UFUNCTION(Server, Reliable)
	void SRPC_SetPlayerId();

	UFUNCTION(Client, Reliable)
	void MRPC_SetPlayerId(int playerId);

    public:
	// imc 추가
	UFUNCTION(BlueprintCallable)
	void SetIMC(UInputMappingContext* imc);

	// 돌발이벤트용 넘어지기 시작
	UFUNCTION(BlueprintCallable)
	void StartTrip();

	// 프로필에 따른 겉모습 수정
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetPlayerAppearance(EPlayerType type);

#pragma endregion

};
