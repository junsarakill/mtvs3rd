// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH_TsetJsonParseLib.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "PSH/PSH_HttpActor.h"
#include "PSH/PSH_HttpDataTable.h"

void UPSH_TsetJsonParseLib::JsonParse(const FString& json, FPSH_HttpDataTable& data)
{
	// �����⸦ �����
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);

	// �Ľ� ����� ���� ���� ���� . MakeShareable ����Ʈ ����Ʈ ������ ���� ���.
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject()); // �޸� ���� 
	// �ؼ��� �Ѵ�.
	/*FPSH_HttpDataTable* newRow = new FPSH_HttpDataTable();*/
	if (FJsonSerializer::Deserialize(reader, result))
	{
// 		TArray<TSharedPtr<FJsonValue>> ParseDatList = result->GetArrayField(TEXT("items"));
// 		for (TSharedPtr<FJsonValue> data : ParseDatList)
// 		{
// 			// å�� �̸��� ����.
// 
//  			FString id = data->AsObject()->GetStringField("id");
//  			FString pw = data->AsObject()->GetStringField("pw");
// // 			FString authorName = data->AsObject()->GetStringField("aut_nm");
//  			//returnValue.Append(FString::Printf(TEXT("BookName : %s / AuthrName : %s\n"), *bookName, *authorName));
//  			returnValue.Append(FString::Printf(TEXT("id : %s \n pw : 5s"), *id, *pw));
// 			// å�� �̸��� ����.
// // 			if (data->AsObject()->HasField("bk_nm")) // �ִ��� Ȯ��
// // 				int age = data->AsObject()->GetIntegerField("123");
// 		
// 		}
		
// 		data.FromUserID1 = result->GetIntegerField("Target_1_Id");
// 		data.FromUserID2 = result->GetIntegerField("Target_2_Id");
// 		data.AffinityScore_ID1 = result->GetNumberField("synchro_1");
// 		data.AffinityScore_ID2 = result->GetNumberField("synchro_2");


		data.testFromUserID = result->GetStringField("FromUserID");
		data.testToUserID = result->GetStringField("ToUserID");
		data.testAffinityScore = result->GetStringField("AffinityScore");
	}

	data.PrintStruct();

	// ��ȯ�Ѵ�.
	//return newRow;
}

FString UPSH_TsetJsonParseLib::MakeJson(const TMap<FString, FString> source)
{
	// source�� jsonObject�������� �����
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());

	for (TPair<FString, FString> pair : source)
	{
		jsonObject->SetStringField(pair.Key, pair.Value);
	}

	// Writer�� ���� jsonObject�� ���ڵ��ؼ� 
	FString json;
	TSharedRef<TJsonWriter<TCHAR>> writer = TJsonWriterFactory<TCHAR>::Create(&json);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef(), writer);

	//��ȯ
	return json;
}
