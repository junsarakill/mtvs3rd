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
	//http ACtor ���� ���������Ͱ��� �޾ƿ���� ��û�϶�� �ϰ�ʹ�.
	// post�� �ȿ� ������ ����ټ� �ְ�
	// Get�� URL�������� ���� ����Ѵ�. URL�ڿ� ������ ��� ������ ���޴´�.

	FString fullURL = FString::Printf(TEXT("%s?id:ke1pw:23"), *URL );

	httpActor->ReqGetTest(fullURL);
}

void UPSH_HttpTestUserWidget::OnMyClickSendPost()
{
	TMap<FString, FString> StudentData; // ���̽��� �� ������
	StudentData.Add("id", "Kei");  // Ű , ����
	StudentData.Add("pw", "23");
	
	FString json = UPSH_TsetJsonParseLib::MakeJson(StudentData);

	httpActor->ReqPostTest(URL, json); // ���� ���̽� �����ִ°�
}

void UPSH_HttpTestUserWidget::SetHttpACtor(class APSH_HttpActor* Actor)
{
	httpActor = Actor;
}

void UPSH_HttpTestUserWidget::SetTextLog(FString log)
{
	TexLog->SetText(FText::FromString(log));
}
