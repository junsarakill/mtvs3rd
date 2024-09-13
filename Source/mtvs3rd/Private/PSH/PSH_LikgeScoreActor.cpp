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
	TMap<FString, FString> LikeScoreData; // 제이슨에 들어갈 데이터
	LikeScoreData.Add("", "");
	LikeScoreData.Add("", "");
	LikeScoreData.Add("", "");
	LikeScoreData.Add("", "");

	FString json = UPSH_TsetJsonParseLib::MakeJson(LikeScoreData);

	LikeScoreButtonReqPost(json, URLScore); // 만든 제이슨 보내주는거
}

void APSH_LikgeScoreActor::LikeScoreButtonReqPost(FString json, FString URL)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// 	// 요청할 정보를 설정
	req->SetURL(URL);
	req->SetVerb(TEXT("Post"));
	req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

	req->SetContentAsString(json); // 내용

	//req->SetTimeout(); 세션 유지 시간 설정.
	// 응답받을 함수를 연결
	req->OnProcessRequestComplete().BindUObject(this, &APSH_LikgeScoreActor::LikeScoreButtonOnResPost);

	// 서버에 요청
	req->ProcessRequest();
}

void APSH_LikgeScoreActor::LikeScoreButtonOnResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 성공
		// actorv controll
		// Json을 파싱해서 필요한 정보만 뽑아서 화면에 출력하고싶다.
		UE_LOG(LogTemp, Warning, TEXT("creal"));
// 		FString result = Response->GetContentAsString();
// 		UPSH_TsetJsonParseLib::JsonParse(result, PlayerData);
// 
// 		Gi->SetStartData(PlayerData);
// 		playerState->SetPlayerData(PlayerData); // 플레이어 데이터 저장
		// 
		// httpUi->SetTextLog(result);
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}

//  시작중 UI 적용
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

