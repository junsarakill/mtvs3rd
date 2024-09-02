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

	//vr ���
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
	if (httpUi) // �׽�Ʈ��
	{
		httpUi->AddToViewport();
		httpUi->SetHttpACtor(this);

		auto* pc = GetWorld()->GetFirstPlayerController();
		pc->SetShowMouseCursor(true);
		pc->SetInputMode(FInputModeUIOnly());
	}

	/* vr����
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
	// �̸� �Ҵ�
	// ������ ����
	 StartData.Age =  Age;  // 2�� ���� // ��ư ������ 1�� �������� 9�Ѿ�� 0���� �ʱ�ȭ
	 StartData.Gender = Gender; // ���� 2�� ����
	 StartData.Name = SetName(Gender); // 
	 StartData.MBTI = Mbti; // ����

	 // ������ 
	 // ���� ���� ������ �ߴ��� 
	 // �������� ������ ��뿡 ȣ����   0 ~ 10 ���� �Ͽ� ������


	 TMap<FString, FString> StudentData; // ���̽��� �� ������
	 StudentData.Add("Age", StartData.Age);  // Ű , ����
	 StudentData.Add("Gender", StartData.Gender);
	 StudentData.Add("MBTI", StartData.MBTI);
	 StudentData.Add("NickName", StartData.Name);

	 FString json = UPSH_TsetJsonParseLib::MakeJson(StudentData);
	 // ���
	 ReqPost(URL, json);
}



FHttopStartData APSH_StartDataHttpActor::GetStartData()
{
	return StartData;
}

void APSH_StartDataHttpActor::ReqPost(FString ServerURL, FString json)
{
	// Http ����� ���� 
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// ��û�� ������ ����
	req->SetURL(ServerURL);
	req->SetVerb(TEXT("Post"));
	req->SetHeader(TEXT("Content-Type"), TEXT("Application/json"));

	req->SetContentAsString(json); // ����

	//req->SetTimeout(); ���� ���� �ð� ����.
	// ������� �Լ��� ����
	req->OnProcessRequestComplete().BindUObject(this, &APSH_StartDataHttpActor::OnResPost);

	// ������ ��û
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
		// ����
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}

