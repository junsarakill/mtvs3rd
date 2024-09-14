// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <Components/ActorComponent.h>
#include <JBS/BS_BillBoardWorldUIActor.h>
#include "BS_SelectConfirmActor.generated.h"



UCLASS()
class MTVS3RD_API ABS_SelectConfirmActor : public ABS_BillBoardWorldUIActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABS_SelectConfirmActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// ui comp
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Component")
	class UWidgetComponent* uiComp;
	// 최종 선택 ui
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Default|Component", BlueprintGetter=GetConfirmUI, BlueprintSetter=SetConfirmUI)
	class UBS_SelectConfirmUI* selectConfirmUI;
		public:
	__declspec(property(get = GetConfirmUI, put = SetConfirmUI)) UBS_SelectConfirmUI* SELECT_CONFIRM_UI;
	UFUNCTION(BlueprintGetter)
	UBS_SelectConfirmUI* GetConfirmUI()
	{
		if(!selectConfirmUI)
			CacheConfirmUI();

		return selectConfirmUI;
	}
	UFUNCTION(BlueprintSetter)
	void SetConfirmUI(UBS_SelectConfirmUI* value);
		protected:
	

public:

	


protected:
	// ui 캐시
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CacheConfirmUI();

public:

};
