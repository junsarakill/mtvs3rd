// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_LikgeScoreActor.h"
#include "Components/WidgetComponent.h"
#include "PSH/PSH_LikeSocreWidget.h"
#include "PSH_TsetJsonParseLib.h"
#include "HttpModule.h"

// Sets default values
APSH_LikgeScoreActor::APSH_LikgeScoreActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	SetRootComponent(Widget);
}

// Called when the game starts or when spawned
void APSH_LikgeScoreActor::BeginPlay()
{
	Super::BeginPlay();
	if (Widget)
	{
		auto * ScoreWidget = Cast<UPSH_LikeSocreWidget>(Widget->GetWidget());
		if (ScoreWidget)
		{
			ScoreWidget->SetLikeSocreOwner(this);
		}
	}
}


void APSH_LikgeScoreActor::Tick(float DeltaSeconds)
{

}

void APSH_LikgeScoreActor::LikeScoreButtonJson()
{
	TMap<FString, FString> LikeScoreData; // ���̽��� �� ������
	LikeScoreData.Add("", "");
	LikeScoreData.Add("", "");
	LikeScoreData.Add("", "");
	LikeScoreData.Add("", "");

	FString json = UPSH_TsetJsonParseLib::MakeJson(LikeScoreData);

	LikeScoreButtonReqPost(json, URLScore); // ���� ���̽� �����ִ°�
}

void APSH_LikgeScoreActor::LikeScoreButtonReqPost(FString json, FString URL)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// 	// ��û�� ������ ����
	req->SetURL(URL);
	req->SetVerb(TEXT("Post"));
	req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

	req->SetContentAsString(json); // ����

	//req->SetTimeout(); ���� ���� �ð� ����.
	// ������� �Լ��� ����
	req->OnProcessRequestComplete().BindUObject(this, &APSH_LikgeScoreActor::LikeScoreButtonOnResPost);

	// ������ ��û
	req->ProcessRequest();
}

void APSH_LikgeScoreActor::LikeScoreButtonOnResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// ����
		// actorv controll
		// Json�� �Ľ��ؼ� �ʿ��� ������ �̾Ƽ� ȭ�鿡 ����ϰ�ʹ�.
		UE_LOG(LogTemp, Warning, TEXT("creal"));
// 		FString result = Response->GetContentAsString();
// 		UPSH_TsetJsonParseLib::JsonParse(result, PlayerData);
// 
// 		Gi->SetStartData(PlayerData);
// 		playerState->SetPlayerData(PlayerData); // �÷��̾� ������ ����
		// 
		// httpUi->SetTextLog(result);
	}
	else
	{
		// ����
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}

//  ������ UI ����
// void APSH_Mtvs3rdGameModBase::QestButtonJson(int ButtonNum, int QestNum, int playerID)
// {
// 	
// }
// 
// void APSH_Mtvs3rdGameModBase::ReqPost()
// {
// 	
// }
// void APSH_Mtvs3rdGameModBase::OnResPost()
// {
// 	
// }

