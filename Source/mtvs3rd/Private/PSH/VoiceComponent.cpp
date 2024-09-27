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

	// VOIP Talker ������Ʈ�� �����ϰ�, VOIPTalkerComponent �����Ϳ� �Ҵ��մϴ�.
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
		// VOIPTalkerComponent�� ��ȿ���� Ȯ���մϴ�.
		if (IsValid(VOIPTalkerComponent))
		{
			// �÷��̾� ���¿� VOIPTalker�� ����մϴ�.
			RegisterWithPlayerState();

			// ����ũ �Ӱ谪�� �����մϴ�.
			SetMicThreshold(-1.0f);
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			
			// ���� �÷��̾ ���� ���� ���� VOIP ���� ������ �����մϴ�.
			if (PlayerController  && PlayerController->IsLocalController())
			{
				// �ܼ� ����� �����Ͽ� VOIP�� Ȱ��ȭ�մϴ�.
				PlayerController->ConsoleCommand("OSS.VoiceLoopback 1");
			}
		}
	}
}