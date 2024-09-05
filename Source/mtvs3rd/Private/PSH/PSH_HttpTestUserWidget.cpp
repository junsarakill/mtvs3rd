// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_HttpTestUserWidget.h"
#include "Components/Button.h"
#include "PSH_TsetJsonParseLib.h"
#include "PSH/PSH_HttpActor.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"

void UPSH_HttpTestUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	

	SendButton->OnClicked.AddDynamic(this, &UPSH_HttpTestUserWidget::OnMyClickSend);

	PostSendButton->OnClicked.AddDynamic(this, &UPSH_HttpTestUserWidget::OnMyClickSendPost);
}

void UPSH_HttpTestUserWidget::OnMyClickSend()
{
	//http ACtor 에게 공공데이터값을 받아오라고 요청하라고 하고싶다.
	// post는 안에 내용을 담아줄수 있고
	// Get은 URL형식으로 만들어서 줘야한다. URL뒤에 형식이 없어서 내용을 못받는다.

	FString fullURL = FString::Printf(TEXT("%s?id:ke1pw:23"), *URL );

	httpActor->ReqGetTest(fullURL);
}

void UPSH_HttpTestUserWidget::OnMyClickSendPost()
{
	TMap<FString, FString> StudentData; // 제이슨에 들어갈 데이터
	StudentData.Add("id", "Kei");  // 키 , 벨류
	StudentData.Add("pw", "23");
	
	FString json = UPSH_TsetJsonParseLib::MakeJson(StudentData);

	httpActor->ReqPostTest(URL, json); // 만든 제이슨 보내주는거
}

void UPSH_HttpTestUserWidget::SetHttpACtor(class APSH_HttpActor* Actor)
{
	httpActor = Actor;
}

void UPSH_HttpTestUserWidget::SetTextLog(FString log)
{
	TexLog->SetText(FText::FromString(log));
}
