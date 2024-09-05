// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "PSH_HttpActor.generated.h"


// actor 클라에서 할당
// 월드에서 할당 하거나 미리 할당해놓거나
// 서버 -> 복제 
// 월드에서 '찾아서' 할당 <- 클라/서버 구분을 안해놓으면 클라
// 


// 클라이언트 -> Ai

// ai -> 모두에게 보여줄 x

// ai <- 모두에게 보여줄 필요


// 처음 입력 데이터

// 제이슨 통신

// 내가 누구고 뭘 선택했는지 ->

// 남자 1 -> 내가 누군지 -> 해당하는 상대 , 싱크로율 << - 제이슨

// 배열 [누구, 1번의 호감도 , 2번의 호감도]

// 제이슨에 제이슨
// 맵 <여자 1, 싱크로율 >;
// 맵 <여자 2 , 싱크로율 >

// 4개 변수 해놓고 

// 구조체 -> 형 모름 시간 금요일 통신까지 알아와서 대화하기로함

// 1, 4 

// AI 에서 데이터 산정하기에 좀 부족하다.

// 시연 을 정해놓고 실행하자.

 // 값을 내가 파싱해서 구조체에 담아두면
 // 임시 데이터 

 // 0 1 2 
 // 남자1 여자1 여자2
 // 남자2 여자1 여자2
 // 여자1 남자1 남자2
 // 여자2 남자1 남자2

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
 struct FHttopData // 인당 구조체 배열.
 {
	GENERATED_USTRUCT_BODY()
 public:

	FString name;
	float sing; // 싱크로율 

 };

 // 구조체 배열로 할지
 // 구조체 안에 인덱스를 늘릴지
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
	void ReqGetTest(FString url); // 웹에서 사용하는 용어  리퀘스트

	// 응답받을 함수
	void OnResGetTest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully); // 웹에서 사용하는 용어  리퀘스트 ResPouse

	// ButtonSendPost를 눌렀을 때 요청할 함수
	void ReqPostTest(FString ServerURL, FString json);

	// 응답받을 함수
	void OnResPostTest(FHttpRequestPtr Request , FHttpResponsePtr Response, bool bConnectedSuccessfully); // 웹에서 사용하는 용어  리퀘스트 ResPouse
};
