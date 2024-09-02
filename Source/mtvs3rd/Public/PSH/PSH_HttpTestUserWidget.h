// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSH_HttpTestUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MTVS3RD_API UPSH_HttpTestUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;

	UPROPERTY()
	class APSH_HttpActor* httpActor;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * TexLog;

	UPROPERTY(meta = (BindWidget))
	class UEditableText * EditPageNo;
	UPROPERTY(meta = (BindWidget))
	class UEditableText * EditNumOfRows;

	UPROPERTY(meta = (BindWidget))
	class UButton * SendButton;
	UPROPERTY(meta = (BindWidget))
	class UButton * PostSendButton;


	UFUNCTION()
	void OnMyClickSend();

	UFUNCTION()
	void OnMyClickSendPost();

	void SetHttpACtor(class APSH_HttpActor* Actor);

	void SetTextLog(FString log);

	FString URL = "192.168.0.14:3111/login";
	//FString URL = "http://127.0.0.1:3111/login";
	
};
