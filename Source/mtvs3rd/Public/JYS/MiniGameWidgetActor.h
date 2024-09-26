// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiniGameMissionWidget.h"
#include "MiniGameQuestionWidget.h"
#include "MiniGameWidgetActor.generated.h"

UCLASS()
class MTVS3RD_API AMiniGameWidgetActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMiniGameWidgetActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // 빌보드
    UFUNCTION()
    void BillBoardQuestionsWidget();

    ////// PC
    // UPROPERTY(EditDefaultsOnly)
    // class TSubclassOf<class UUserWidget> pcWidgetFactory1;
    //
    ////// PC
    // UPROPERTY(EditDefaultsOnly)
    // class TSubclassOf<class UUserWidget> pcWidgetFactory2;

    ////// PC
    // UPROPERTY()
    // class UQuestionsWidget* pcWiidget;

    // VR
    UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* miniGameUIComp;    
    
    UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* missionWidgetUI;    
    
    UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* countDownWidget;

    UPROPERTY(EditDefaultsOnly)
    class ACharacter *player;

    void InitUI();

    bool bCheck = false;

public:

	UPROPERTY(BlueprintReadOnly)
	int32 minutes = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 second = 60;

    UFUNCTION()
    void HideMissionWidget();

    UPROPERTY()
    class UMiniGameMissionWidget *missionWidget;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AActor> actor;

    TArray<AActor *> findTB;

    AActor *closestActor;
    
    UPROPERTY(EditDefaultsOnly)
    class AMiniGameTriggerBox_Item *triggerBox;

};
