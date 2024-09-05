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
	// Http ����� ���� 
	FHttpModule& httpModule = FHttpModule::Get();
	//TSharedRef<IHttpRequest> req =httpModule.CreateRequest(); �Ʒ��� ����
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// ��û�� ������ ����
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));
	//req->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

	// ������� �Լ��� ����
	req->OnProcessRequestComplete().BindUObject(this, &APSH_HttpActor::OnResGetTest);

	// ������ ��û
	req->ProcessRequest();
}

void APSH_HttpActor::OnResGetTest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// ����
		FString result = Response->GetContentAsString();

		// Json�� �Ľ��ؼ� �ʿ��� ������ �̾Ƽ� ȭ�鿡 ����ϰ�ʹ�.
		//httpUi->SetTextLog(UPSH_TsetJsonParseLib::JsonParse(result));
	}
	else
	{
		// ����
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}

void APSH_HttpActor::ReqPostTest(FString ServerURL, FString json)
{
	// Http ����� ���� 
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// ��û�� ������ ����
	req->SetURL(ServerURL);
	req->SetVerb(TEXT("Post"));
	req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

	req->SetContentAsString(json); // ����

	//req->SetContentAsString(json);
	
	//req->SetTimeout(); ���� ���� �ð� ����.
	// ������� �Լ��� ����
	req->OnProcessRequestComplete().BindUObject(this, &APSH_HttpActor::OnResPostTest);

	// ������ ��û
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
		// ����
		// actorv controll
		// 
		// 
		// Json�� �Ľ��ؼ� �ʿ��� ������ �̾Ƽ� ȭ�鿡 ����ϰ�ʹ�.
		FString result = Response->GetContentAsString();
		UE_LOG(LogTemp,Warning,TEXT("%s"), *result);
		// 
		// httpUi->SetTextLog(result);
	}
	else
	{
		// ����
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}

