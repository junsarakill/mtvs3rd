// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include "GameFramework/Actor.h"
#include "PSH/PSH_HttpDataTable.h"
#include "BS_Hand.generated.h"

UENUM(BlueprintType)
enum class EMotionControllerType : uint8
{
	LEFT
	,RIGHT
};

USTRUCT(BlueprintType)
struct FControllerType
{
	GENERATED_BODY()

	// 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	EMotionControllerType type;
	// 메시
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	class USkeletalMesh* mesh;
	// 위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	FVector loc;
	// 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	FRotator rot;
};

UCLASS()
class MTVS3RD_API ABS_Hand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABS_Hand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	// 나를 소유한 플레이어
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Objects")
	class ABS_VRPlayer* ownerPlayer;

	
	// 모션 루트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class USceneComponent* motionRoot;

	// 컨트롤러
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class UMotionControllerComponent* motionController;
	// 에임 컨트롤러
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class UMotionControllerComponent* aimMC;
	// ui 상호작용
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class UWidgetInteractionComponent* uiInteractComp;
	// 손 루트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class USceneComponent* handRoot;
	// 손 메시
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class USkeletalMeshComponent* handMesh;
	// 최종 선택 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Component")
	class UBS_FinalSelectComponent* fsComp;

	// FIXME 프로토 타입용 더미 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Debug")
	FPSH_HttpDataTable dummyData;

	// 더미용 id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	int32 dummyID = 0;





	// 레이 활/비
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values", BlueprintGetter=GetEnableRay, BlueprintSetter=SetEnableRay)
	bool enableRay = false;
		public:
	__declspec(property(get = GetEnableRay, put = SetEnableRay)) bool ENABLE_RAY;
	UFUNCTION(BlueprintCallable, BlueprintGetter)
	bool GetEnableRay()
	{
		return enableRay;
	}
	UFUNCTION(BlueprintCallable, BlueprintSetter)
	void SetEnableRay(bool value);
		protected:

	// 컨트롤러 종류
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	EMotionControllerType cType;

	// 컨트롤러 데이터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	TArray<FControllerType> typeData;

	// 물건 잡았는지 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values")
	bool isGrab = false;
	// 현재 잡은 액터
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Objects")
	class ABS_GrabbableActor* grabActor;

	// 잡기 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	float grabRadius = 6.f;

	// 현재 잡은 그랩 컴포
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Objects")
	class UBS_GrabComponent* curGrabComp;
		

	// 원거리 잡기 가능 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Values", BlueprintGetter=GetCanRangeGrab, BlueprintSetter=SetCanRangeGrab)
	bool canRangeGrab = false;
		public:
	__declspec(property(get = GetCanRangeGrab, put = SetCanRangeGrab)) bool CAN_RANGE_GRAB;
	UFUNCTION(BlueprintGetter)
	bool GetCanRangeGrab()
	{
		return canRangeGrab;
	}
	UFUNCTION(BlueprintSetter)
	void SetCanRangeGrab(bool value);

    protected:

	// 찾은 원거리 grabcomp
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Objects")
	class UBS_GrabComponent* curFindGrabComp;
		public:
	__declspec(property(get = GetCurFindGrabComp, put = SetCurFindGrabComp)) class UBS_GrabComponent* CUR_FIND_GRAB_COMP;
	class UBS_GrabComponent* GetCurFindGrabComp()
	{
		return curFindGrabComp;
	}
	void SetCurFindGrabComp(class UBS_GrabComponent *value);

		protected:

	// XXX 디버그용 잡기 범위 표시
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Debug")
	bool enableDebugGrabSphere = false;

	// 플레이어 프로필 ui 프리팹
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	TSubclassOf<class ABS_ProfileWorldUIActor> profileUIActorPrefab;

	// 프로필 ui
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Objects")
	class ABS_ProfileWorldUIActor* profileUIActor;
	
	// ui 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Component")
	class UArrowComponent* profileUIPos;

	//ui 상호작용 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values", BlueprintGetter=GetRayInteractDis, BlueprintSetter=SetRayInteractDis)
	float rayInteractDis = 2000.f;
		public:
	__declspec(property(get = GetRayInteractDis, put = SetRayInteractDis)) float RAY_INTERACT_DIS;
	UFUNCTION(BlueprintGetter)
	float GetRayInteractDis()
	{
		return rayInteractDis;
	}
	UFUNCTION(BlueprintSetter)
	void SetRayInteractDis(float value);
		protected:


public:
	UFUNCTION(BlueprintCallable)
	void SetController(EMotionControllerType type, ABS_VRPlayer* player);

	// 핸드 메시 설정
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetHandMesh(EMotionControllerType type);

	// 해당 액터 잡기로 설정
	void SetGrabActor(ABS_GrabbableActor* actor);

	// 잡기 시도
	UFUNCTION(BlueprintCallable)
	bool TryGrab();
	// 잡기
	UFUNCTION(BlueprintCallable)
	bool Grab(class UBS_GrabComponent* grabComp);
	// 놓기
	UFUNCTION(BlueprintCallable)
	bool TryRelease();

	// 주변에 잡을 것이 있는지 찾기
	class UBS_GrabComponent* FindGrabComponentNearHand();

	// ui 클릭
	UFUNCTION(BlueprintCallable)
	void EventPressLMB();
	UFUNCTION(BlueprintCallable)
	void EventReleaseLMB();

	// ray로 플레이어 감지
	void LineTracePlayer();

	// 프로필 ui 생성
	void SpawnProfileUI(FPSH_HttpDataTable otherPlayerData);

	// 프로필 ui 제거
	UFUNCTION(BlueprintCallable)
	void DeleteProfileUI();

	// 원거리 물건 잡기용 물건 찾기
	void FindGrabComponentByRay(class UBS_GrabComponent*& findGrabComp);
};
