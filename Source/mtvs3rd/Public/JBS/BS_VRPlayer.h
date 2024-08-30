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

#pragma region 변수 영역
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class USceneComponent* vrRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class UCameraComponent* vrHMDCam;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class ABS_Hand* leftController;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Components")
	class ABS_Hand* rightController;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
	float cameraHeight = 166.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Classes")
	class UInputMappingContext* imcDefault;

public:

#pragma endregion
#pragma region 함수 영역
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UFUNCTION(BlueprintCallable)
	void SetIMC(UInputMappingContext* imc);

public:

#pragma endregion

};
