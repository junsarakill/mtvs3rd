// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "PSH_TsetJsonParseLib.h"
#include "PSH/PSH_HttpDataTable.h"
#include "HttpModule.h"

void APSH_Mtvs3rdGameModBase::SetStartData(FPSH_HttpDataTable Data)
{

	PlayerData = Data;

	id++;
	PlayerData.Id = id;
	FName RowName = FName(FString::FromInt(id));

	DataTable->AddRow(RowName, PlayerData); // ������ ���̺� �߰�.

	StatDataJson();

	PlayerData.PrintStruct();
	// ������ ���̺� �̸����� ���� �Ͽ� �ش� ���� ����
	//TArray<FPSH_HttpDataTable*> FoundData;
	//FPSH_HttpDataTable * FoundData  = DataTable->FindRow<FPSH_HttpDataTable>(RowName, TEXT("Looking up player data"));
	
	//DataTable->GetAllRows(TEXT(""), FoundData);
	
// 	for (int i = 0; i < FoundData.Num(); i++)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Name: %s, Age: %d, Gender: %s, MBTI : %s"),
// 			*FoundData[i]->Name, FoundData[i]->Age, *FoundData[i]->Gender, *FoundData[i]->MBTI);
// 	}

// 	if (FoundData)
// 	{
// 		// �ش� �࿡ ����� ���� �����´�.
// 		UE_LOG(LogTemp, Warning, TEXT("Name: %s, Age: %d, Gender: %s, MBTI : %s"),
// 			*FoundData->Name, FoundData->Age, *FoundData->Gender,*FoundData->MBTI);
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Row not found in DataTable."));
// 	}

}



void APSH_Mtvs3rdGameModBase::StatDataJson()
{
	TMap<FString, FString> StartData; // ���̽��� �� ������
	StartData.Add("ID", FString::FromInt(PlayerData.Id));  // Ű , ����
	StartData.Add("Name", PlayerData.Name);
	StartData.Add("Gander", PlayerData.Gender);
	StartData.Add("MBTI", PlayerData.MBTI);
	StartData.Add("blood", PlayerData.Blood);


// 	TMap<FString, FPSH_HttpDataTable> StudentData; // ���̽��� �� ������
// 	StudentData.Add("" , PlayerData);

	FString json = UPSH_TsetJsonParseLib::MakeJson(StartData);

	ReqPost(json); // ���� ���̽� �����ִ°�
}

void APSH_Mtvs3rdGameModBase::QestButtonJson(int num)
{
	TMap<FString, FString> StudentData; // ���̽��� �� ������
	StudentData.Add("Answer", FString::FromInt(num));  // Ű , ����
	
	FString json = UPSH_TsetJsonParseLib::MakeJson(StudentData);

	ReqPost(json); // ���� ���̽� �����ִ°�
}

void APSH_Mtvs3rdGameModBase::ReqPost(FString json)
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
	 	req->OnProcessRequestComplete().BindUObject(this, &APSH_Mtvs3rdGameModBase::OnResPost);
	 
	 	// ������ ��û
	 	req->ProcessRequest();
}

void APSH_Mtvs3rdGameModBase::OnResPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// ����
		// actorv controll
		// 
		// 
		// Json�� �Ľ��ؼ� �ʿ��� ������ �̾Ƽ� ȭ�鿡 ����ϰ�ʹ�.
		UE_LOG(LogTemp, Warning, TEXT("����"));
		FString result = Response->GetContentAsString();
		UPSH_TsetJsonParseLib::JsonParse(result, PlayerData);
		
		// 
		// httpUi->SetTextLog(result);
	}
	else
	{
		// ����
		UE_LOG(LogTemp, Warning, TEXT("ReQuestFailed..."));
	}
}
