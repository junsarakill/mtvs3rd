// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "PSH_StartDataHttpActor.generated.h"

USTRUCT(Atomic,BlueprintType) // ���� ��� ������
 struct FHttopStartData
 {
	GENERATED_USTRUCT_BODY()
 public:

	 UPROPERTY()
	 FString Age;  // 2�� ���� // ��ư ������ 1�� �������� 9�Ѿ�� 0���� �ʱ�ȭ
	  UPROPERTY()
	 FString Name; // �������� ������
	  UPROPERTY()
	 FString Gender; // ���� 2�� ����
	  UPROPERTY()
	 FString MBTI; // ����

	 // ISTJ , ISFJ , IMFJ , INTJ , 
	 // ISTP , ISFP , INFP , INTP
	 // ESTP , ESFP , ENFP , ENTP
	 // ESTJ , ESFJ , ENFJ , ENTJ
 };
UCLASS()
class MTVS3RD_API APSH_StartDataHttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APSH_StartDataHttpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HttpUiFact;

	UPROPERTY()
	class UPSH_StartDataWidget* httpUi;

	UPROPERTY()
	FHttopStartData StartData;

// 	UPROPERTY(EditDefaultsOnly)
// 	class UWidgetComponent * SelectComponent;

// 	UPROPERTY(EditDefaultsOnly)
// 	class TSubclassOf<UUserWidget> HttpWidgetFac;

	UPROPERTY(EditDefaultsOnly)
	class UPSH_StartDataWidget * HttpWidget;

	void SetStartData(FString Gender, FString Age , FString Mbti );

	FString SetName(FString Gender);
	FHttopStartData GetStartData();

	// ButtonSendPost�� ������ �� ��û�� �Լ�
	void ReqPost(FString ServerURL, FString json);

	// ������� �Լ�
	void OnResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

private:
	
	FString URL = "192.168.0.14:3111/userinfo";
	TArray<FString> ManNameArray;
	TArray<FString> WomanNameArray;
	
};
