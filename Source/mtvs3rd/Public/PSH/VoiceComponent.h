// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VoiceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTVS3RD_API UVoiceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVoiceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	// VOIP Talker ������Ʈ�� �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Voice Chat", meta = (AllowPrivateAccess = "true"))
	class UVOIPTalker* VOIPTalkerComponent;

	// ����ũ �Ӱ谪�� �����մϴ�.
	void SetMicThreshold(float Threshold);

	// �÷��̾� ���¿� ����մϴ�.
	void RegisterWithPlayerState();

	// ���� �÷��̾ ���� ������ Ȯ���մϴ�.
	/*bool IsLocallyControlled() const;*/

	// VOIP ���� �ʱ�ȭ �۾��� �����մϴ�.
	void InitializeVOIP();

	class ABS_VRPlayer * owner;
};
