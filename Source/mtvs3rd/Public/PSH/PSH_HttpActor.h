// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "PSH_HttpActor.generated.h"


// actor Ŭ�󿡼� �Ҵ�
// ���忡�� �Ҵ� �ϰų� �̸� �Ҵ��س��ų�
// ���� -> ���� 
// ���忡�� 'ã�Ƽ�' �Ҵ� <- Ŭ��/���� ������ ���س����� Ŭ��
// 


// Ŭ���̾�Ʈ -> Ai

// ai -> ��ο��� ������ x

// ai <- ��ο��� ������ �ʿ�


// ó�� �Է� ������

// ���̽� ���

// ���� ������ �� �����ߴ��� ->

// ���� 1 -> ���� ������ -> �ش��ϴ� ��� , ��ũ���� << - ���̽�

// �迭 [����, 1���� ȣ���� , 2���� ȣ����]

// ���̽��� ���̽�
// �� <���� 1, ��ũ���� >;
// �� <���� 2 , ��ũ���� >

// 4�� ���� �س��� 

// ����ü -> �� �� �ð� �ݿ��� ��ű��� �˾ƿͼ� ��ȭ�ϱ����

// 1, 4 

// AI ���� ������ �����ϱ⿡ �� �����ϴ�.

// �ÿ� �� ���س��� ��������.

 // ���� ���� �Ľ��ؼ� ����ü�� ��Ƶθ�
 // �ӽ� ������ 

 // 0 1 2 
 // ����1 ����1 ����2
 // ����2 ����1 ����2
 // ����1 ����1 ����2
 // ����2 ����1 ����2

 // map<string,map<string,string>>
 // map<string , json>;
 // map<string , int[]>;
//  {
// 	 ary : 
// 	 {
// 		 Name : asd,
// 		 sync : float
// 	 },
// 	 {
// 		 Name: asd,
// 		 sync : float
// 	 }
//  }


 USTRUCT(Atomic,BlueprintType)
 struct FHttopData // �δ� ����ü �迭.
 {
	GENERATED_USTRUCT_BODY()
 public:

	FString name;
	float sing; // ��ũ���� 

 };

 // ����ü �迭�� ����
 // ����ü �ȿ� �ε����� �ø���
 //TArray<FHttopData> asd;
 
UCLASS()
class MTVS3RD_API APSH_HttpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APSH_HttpActor();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:




	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HttpUiFact;

	UPROPERTY()
	class UPSH_HttpTestUserWidget* httpUi;

	//send Clicked FUNCTION
	void ReqGetTest(FString url); // ������ ����ϴ� ���  ������Ʈ

	// ������� �Լ�
	void OnResGetTest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully); // ������ ����ϴ� ���  ������Ʈ ResPouse

	// ButtonSendPost�� ������ �� ��û�� �Լ�
	void ReqPostTest(FString ServerURL, FString json);

	// ������� �Լ�
	void OnResPostTest(FHttpRequestPtr Request , FHttpResponsePtr Response, bool bConnectedSuccessfully); // ������ ����ϴ� ���  ������Ʈ ResPouse
};
