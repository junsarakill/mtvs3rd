// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_JsonParseLibrary.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"


void UPSH_JsonParseLibrary::JsonParse(const FString& json, FPSH_HttpDataTable& data)
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
			// 만약 데이터가 True일 경우

		data.otherUserID1 = FCString::Atoi(*result->GetStringField(TEXT("Target_1_Id")));
		data.otherUserID2 = FCString::Atoi(*result->GetStringField(TEXT("Target_2_Id")));
		data.syncPercentID1 = FCString::Atoi(*result->GetStringField(TEXT("synchro_1")));
		data.syncPercentID2 = FCString::Atoi(*result->GetStringField(TEXT("synchro_2")));
	}

	data.PrintStruct();

	// ��ȯ�Ѵ�.
	//return newRow;
}

FString UPSH_JsonParseLibrary::MakeJson(const TMap<FString, FString> source)
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

FString UPSH_JsonParseLibrary::ProtocolJson(const FString& json)
{
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);

	// �Ľ� ����� ���� ���� ���� . MakeShareable ����Ʈ ����Ʈ ������ ���� ���.
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject()); // �޸� ����
	// �ؼ��� �Ѵ�.
	/*FPSH_HttpDataTable* newRow = new FPSH_HttpDataTable();*/
	if (FJsonSerializer::Deserialize(reader, result))
	{
		return result->GetStringField(TEXT("SuccessFailed")); // 성공 실패 여부
	}
	else
	{
		return "Null";
	}
}

void UPSH_JsonParseLibrary::StartJsonParse(const FString& json, FPSH_HttpDataTable& data)
{
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);

	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(reader, result))
	{
		data.Name = *result->GetStringField(TEXT("Name"));
		data.Gender = *result->GetStringField(TEXT("Gender"));
	}
}
