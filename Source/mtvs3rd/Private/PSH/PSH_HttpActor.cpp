// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_HttpActor.h"
#include <HttpModule.h>
#include "PSH_TsetJsonParseLib.h"
#include "HttpFwd.h"
#include "PSH/PSH_HttpTestUserWidget.h"

// Sets default values
APSH_HttpActor::APSH_HttpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APSH_HttpActor::BeginPlay()
{
	Super::BeginPlay();
	
	httpUi = Cast<UPSH_HttpTestUserWidget>(CreateWidget(GetWorld(), HttpUiFact));

	if (httpUi)
	{
		httpUi->AddToViewport();
		httpUi->SetHttpACtor(this);

		auto* pc = GetWorld()->GetFirstPlayerController();
		pc->SetShowMouseCursor(true);
		pc->SetInputMode(FInputModeUIOnly());
	}
}

// Called every frame
void APSH_HttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APSH_HttpActor::ReqGetTest(FString url)
{
	// Http 모듈을 생성 
	FHttpModule& httpModule = FHttpModule::Get();
	//TSharedRef<IHttpRequest> req =httpModule.CreateRequest(); 아래위 같음
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// 요청할 정보를 설정
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));
	//req->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

	// 응답받을 함수를 연결
	req->OnProcessRequestComplete().BindUObject(this, &APSH_HttpActor::OnResGetTest);

	// 서버에 요청
	req->ProcessRequest();
}

void APSH_HttpActor::OnResGetTest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 성공
		FString result = Response->GetContentAsString();

		// Json을 파싱해서 필요한 정보만 뽑아서 화면에 출력하고싶다.
		//httpUi->SetTextLog(UPSH_TsetJsonParseLib::JsonParse(result));
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}

void APSH_HttpActor::ReqPostTest(FString ServerURL, FString json)
{
	// Http 모듈을 생성 
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// 요청할 정보를 설정
	req->SetURL(ServerURL);
	req->SetVerb(TEXT("Post"));
	req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

	req->SetContentAsString(json); // 내용

	//req->SetContentAsString(json);
	
	//req->SetTimeout(); 세션 유지 시간 설정.
	// 응답받을 함수를 연결
	req->OnProcessRequestComplete().BindUObject(this, &APSH_HttpActor::OnResPostTest);

	// 서버에 요청
	req->ProcessRequest(); 
}

// mod -> player [0] 
// man 2
// gul 2

 // set hogamdo
 // ai 


// who -> what Eveint value; 
// 
// g1 <-> m2 , m1; 
// m1 <-> g2 
// g1 -> m1
// g1 -> m2

// 

void APSH_HttpActor::OnResPostTest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 성공
		// actorv controll
		// 
		// 
		// Json을 파싱해서 필요한 정보만 뽑아서 화면에 출력하고싶다.
		FString result = Response->GetContentAsString();
		UE_LOG(LogTemp,Warning,TEXT("%s"), *result);
		// 
		// httpUi->SetTextLog(result);
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}

