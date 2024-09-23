// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniGameQuestionWidget.generated.h"

/**
 *
 */
UCLASS()
class MTVS3RD_API UMiniGameQuestionWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;

    UPROPERTY(meta = (BindWidget))
    class UButton *btn_1;

    UPROPERTY(meta = (BindWidget))
    class UButton *btn_2;

    UPROPERTY(meta = (BindWidget))
    class UButton *btn_3;

    UPROPERTY(meta = (BindWidget))
    class UButton *btn_4;

    UPROPERTY(meta = (BindWidget))
    class UButton *btn_5;

    UPROPERTY(meta = (BindWidget))
    class UButton *btn_6;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *QuestionBtn;

    void SetOwner(class AMiniGameWidgetActor *miniActor);

    TArray<class AActor *> tag;

private:
    UFUNCTION()
    void Onbtn_1Clicked();

    UFUNCTION()
    void Onbtn_2Clicked();

    UFUNCTION()
    void Onbtn_3Clicked();

    UFUNCTION()
    void Onbtn_4Clicked();

    UFUNCTION()
    void Onbtn_5Clicked();

    UFUNCTION()
    void Onbtn_6Clicked();

    UPROPERTY(EditDefaultsOnly)
    class AMiniGameWidgetActor *owner;

    UPROPERTY(EditDefaultsOnly)
    class AMiniGameTriggerBox_Item *triggerBox;


    UFUNCTION()
    void StartCountDown();

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AActor> actor;

    TArray<AActor *> findTB;

    
    UPROPERTY(BlueprintReadOnly)
    int32 minutes = 2;
    UPROPERTY(BlueprintReadOnly)
    int32 second = 59;
};
