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

    // ������
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
    class ACharacter *player;

    //UPROPERTY(EditDefaultsOnly)
    //TSubclassOf<UMiniGameMissionWidget> MissionWidgetFactory;

    //UPROPERTY(EditDefaultsOnly)
    //TSubclassOf<UMiniGameQuestionWidget> QuestionWidgetFactory;

    void InitUI();

    bool bCheck = false;

public:
    // countdown
    void CountDown();

    UPROPERTY(BlueprintReadOnly)
    int32 minutes = 2;
    UPROPERTY(BlueprintReadOnly)
    int32 second = 59;

    UFUNCTION()
    void HideMissionWidget();

    UPROPERTY()
    class UMiniGameMissionWidget *missionWidget;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AActor> actor;

    TArray<AActor *> findTB;

    AActor *closestActor;

    // jbs 수정
    // 남자 일때만 정답 선택 ui 뜨게하기
    UFUNCTION(Server, Reliable)
    void SRPC_SetVisibilityByGender();

    UFUNCTION(NetMulticast, Reliable)
    void MRPC_SetVisibilityByGender(struct FPSH_HttpDataTable playerData);
};
