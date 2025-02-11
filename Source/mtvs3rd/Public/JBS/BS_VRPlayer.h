// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include "GameFramework/Character.h"
#include <PSH/PSH_HttpDataTable.h>
#include <JBS/BS_Utility.h>
#include <JBS/BS_PlayerState.h>
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	bool isSnapTurn = true;

	// 스냅턴 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	float snapTurnDeg = 45.f;

	// 회전 배율
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	float smoothTurnMulti = 5.f;

#pragma region 디버그 변수
	// 디버그용 최종 선택 가능
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Debug")
	bool enableDebugFinalSelect = false;

	// pc 모드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Debug")
	bool playOnPC = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Debug")
	bool enableViewPlayerStat = true;

#pragma endregion

#pragma region 프리팹

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	class UInputMappingContext* imcDefault;

	// 플레이어 외형 데이터 맵
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	TMap<EPlayerType, FPlayerAppearanceData> playerAppearanceMap;
	

#pragma endregion

#pragma region 컴포넌트, 오브젝트
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
	// vr 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class UCameraComponent* vrHMDCam;
	// 컨트롤러
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category="Default|Components")
	class ABS_Hand* leftController;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category="Default|Components")
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

	// 스냅턴
	void SnapTurn(bool isRight);

	//자연스러운 회전
	void SmoothTurn(float value);

	// 마우스 회전
	UFUNCTION(BlueprintCallable)
	void EventLookup(FVector2D value);
	

public:
	// imc 추가
	UFUNCTION(BlueprintCallable)
	void SetIMC(UInputMappingContext* imc);

	// 돌발이벤트용 넘어지기 시작
	UFUNCTION(BlueprintCallable)
	void StartTrip();

	// 프로필에 따른 겉모습 수정
	// XXX
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetPlayerAppearance(EPlayerType type);

	UFUNCTION(BlueprintCallable)
	void SetPlayerAppearance2(EPlayerType type);

	UFUNCTION(Server, Reliable)
	void SRPC_CalcPlayerType(EPlayerType type);

	UFUNCTION(NetMulticast, Reliable)
	void MRPC_CalcPlayerType(EPlayerType pType);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void SRPC_DebugPlayerStat();

	UFUNCTION(NetMulticast, Reliable)
	void MRPC_DebugPlayerStat(const FString &playerStatStr);

#pragma endregion

};
