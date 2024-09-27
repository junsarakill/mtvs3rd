// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/VoiceComponent.h"
#include "JBS/BS_VRPlayer.h"
#include "Net/VoiceConfig.h"
#include "JBS/BS_PlayerState.h"

// Sets default values for this component's properties
UVoiceComponent::UVoiceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// VOIP Talker 컴포넌트를 생성하고, VOIPTalkerComponent 포인터에 할당합니다.
	VOIPTalkerComponent = CreateDefaultSubobject<UVOIPTalker>(TEXT("VOIPTalker"));
	// ...
}


// Called when the game starts
void UVoiceComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner<ABS_VRPlayer>();

	
	if (owner)
	{
		InitializeVOIP();
	}
}


// Called every frame
void UVoiceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UVoiceComponent::SetMicThreshold(float Threshold)
{
	if (VOIPTalkerComponent)
	{
		UVOIPStatics::SetMicThreshold(Threshold);
	}
}
void UVoiceComponent::RegisterWithPlayerState()
{
	if (VOIPTalkerComponent && owner->GetPlayerState<ABS_PlayerState>())
	{
		VOIPTalkerComponent->RegisterWithPlayerState(owner->GetPlayerState<ABS_PlayerState>());
	}
}
void UVoiceComponent::InitializeVOIP()
{
	if (VOIPTalkerComponent)
	{
		// VOIPTalkerComponent가 유효한지 확인합니다.
		if (IsValid(VOIPTalkerComponent))
		{
			// 플레이어 상태에 VOIPTalker를 등록합니다.
			RegisterWithPlayerState();

			// 마이크 임계값을 설정합니다.
			SetMicThreshold(-1.0f);
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			
			// 로컬 플레이어가 제어 중일 때만 VOIP 관련 설정을 진행합니다.
			if (PlayerController  && PlayerController->IsLocalController())
			{
				// 콘솔 명령을 실행하여 VOIP를 활성화합니다.
				PlayerController->ConsoleCommand("OSS.VoiceLoopback 1");
			}
		}
	}
}