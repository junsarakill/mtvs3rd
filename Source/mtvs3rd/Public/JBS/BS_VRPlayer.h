// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	float moveSpeed = 600.f;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	class UInputMappingContext* imcDefault;

	// 플레이어 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Objects")
	class ABS_PlayerState* ps;
		public:
	__declspec(property(get = GetPS, put = SetPS)) ABS_PlayerState* PS;
	ABS_PlayerState* GetPS()
	{
		// ps 캐시 안되있으면 가져오기
		if(!ps)
		{
			auto* myPS = this->GetPlayerState<ABS_PlayerState>();
			check(myPS);
			// ps 로 뭔가하기
			ps = myPS;
		}

		return ps;
	}
	void SetPS(ABS_PlayerState* value);
		protected:


	// XXX 디버그용 최종 선택 가능
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Debug")
	bool enableDebugFinalSelect = false;

	
	

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
#pragma region 함수 영역
protected:
	// imc 추가
	UFUNCTION(BlueprintCallable)
	void SetIMC(UInputMappingContext* imc);

	// 이동속도 설정
	void SetMoveSpeed(float value);
	// 이동방향 설정
	UFUNCTION(BlueprintCallable)
	void SetMoveDir(FVector2D dir);

	// 썸스틱으로 회전
	UFUNCTION(BlueprintCallable)
	void EventTurn(float value);

	void SnapTurn(bool isRight);

public:

#pragma endregion

};
