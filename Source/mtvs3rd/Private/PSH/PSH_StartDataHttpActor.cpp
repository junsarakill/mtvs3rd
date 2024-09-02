// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_StartDataHttpActor.h"
#include "Components/WidgetComponent.h"
#include "PSH/PSH_StartDataWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PSH_TsetJsonParseLib.h"
#include "HttpModule.h"

// Sets default values
APSH_StartDataHttpActor::APSH_StartDataHttpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//vr 모드
// 	SelectComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("SelectUi"));
// 	SelectComponent->SetupAttachment(RootComponent);
// 	
// 	ConstructorHelpers::FClassFinder<UUserWidget> TempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/PSH/Blueprints/UI/WBP_PSH_StartDataWidget.WBP_PSH_StartDataWidget_C'"));
// 
// 	if (TempWidget.Succeeded())
// 	{
// 		SelectComponent->SetWidgetClass(TempWidget.Class);
// 		SelectComponent->SetDrawSize(FVector2D(1920,1080));
// 	}
}

// Called when the game starts or when spawned
void APSH_StartDataHttpActor::BeginPlay()
{
	Super::BeginPlay();


	httpUi = Cast<UPSH_StartDataWidget>(CreateWidget(GetWorld(), HttpUiFact));
	if (httpUi) // 테스트용
	{
		httpUi->AddToViewport();
		httpUi->SetHttpACtor(this);

		auto* pc = GetWorld()->GetFirstPlayerController();
		pc->SetShowMouseCursor(true);
		pc->SetInputMode(FInputModeUIOnly());
	}

	/* vr전용
	if (SelectComponent)
	{
		HttpWidget = Cast<UPSH_StartDataWidget>(SelectComponent->GetWidget());
		if (HttpWidget)
		{
			HttpWidget->SetHttpACtor(this);
			UE_LOG(LogTemp, Warning, TEXT("HttpWidget : %s"), *HttpWidget->GetClass()->GetName());
		}
	}
	*/

}

// Called every frame
void APSH_StartDataHttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

FString APSH_StartDataHttpActor::SetName(FString Gender)
{
	if (Gender == "Man")
	{
		return "YeongCheol";
	}
	else
	{
		return "Oksun";
	}
}
void APSH_StartDataHttpActor::SetStartData(FString Gender, FString Age, FString Mbti)
{
	// 이름 할당
	// 데이터 저장
	 StartData.Age =  Age;  // 2개 선택 // 버튼 누르면 1씩 더해지고 9넘어가면 0으로 초기화
	 StartData.Gender = Gender; // 성별 2개 선택
	 StartData.Name = SetName(Gender); // 
	 StartData.MBTI = Mbti; // 선택

	 // 혈액형 
	 // 누가 무슨 선택을 했는지 
	 // 스테이지 끝날때 상대에 호감도   0 ~ 10 선택 하여 보내기


	 TMap<FString, FString> StudentData; // 제이슨에 들어갈 데이터
	 StudentData.Add("Age", StartData.Age);  // 키 , 벨류
	 StudentData.Add("Gender", StartData.Gender);
	 StudentData.Add("MBTI", StartData.MBTI);
	 StudentData.Add("NickName", StartData.Name);

	 FString json = UPSH_TsetJsonParseLib::MakeJson(StudentData);
	 // 통신
	 ReqPost(URL, json);
}



FHttopStartData APSH_StartDataHttpActor::GetStartData()
{
	return StartData;
}

void APSH_StartDataHttpActor::ReqPost(FString ServerURL, FString json)
{
	// Http 모듈을 생성 
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// 요청할 정보를 설정
	req->SetURL(ServerURL);
	req->SetVerb(TEXT("Post"));
	req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

	req->SetContentAsString(json); // 내용

	//req->SetTimeout(); 세션 유지 시간 설정.
	// 응답받을 함수를 연결
	req->OnProcessRequestComplete().BindUObject(this, &APSH_StartDataHttpActor::OnResPost);

	// 서버에 요청
	req->ProcessRequest();
}

void APSH_StartDataHttpActor::OnResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		UE_LOG(LogTemp, Warning, TEXT("ReQuest..."));
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}

