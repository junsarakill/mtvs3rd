// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH_TsetJsonParseLib.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"

FString UPSH_TsetJsonParseLib::JsonParse(const FString& json)
{
	// �����⸦ �����
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);

	// �Ľ� ����� ���� ���� ���� . MakeShareable ����Ʈ ����Ʈ ������ ���� ���.
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject()); // �޸� ���� 
	// �ؼ��� �Ѵ�.
	FString returnValue;
	if (FJsonSerializer::Deserialize(reader, result))
	{
		TArray<TSharedPtr<FJsonValue>> ParseDatList = result->GetArrayField(TEXT("items"));
		for (TSharedPtr<FJsonValue> data : ParseDatList)
		{
			// å�� �̸��� ����.

 			FString id = data->AsObject()->GetStringField("id");
 			FString pw = data->AsObject()->GetStringField("pw");
// 			FString authorName = data->AsObject()->GetStringField("aut_nm");
 			//returnValue.Append(FString::Printf(TEXT("BookName : %s / AuthrName : %s\n"), *bookName, *authorName));
 			returnValue.Append(FString::Printf(TEXT("id : %s \n pw : 5s"), *id, *pw));
			// å�� �̸��� ����.
// 			if (data->AsObject()->HasField("bk_nm")) // �ִ��� Ȯ��
// 				int age = data->AsObject()->GetIntegerField("123");
		
		}
	}

	// ��ȯ�Ѵ�.
	return returnValue;
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
