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
		data.testFromUserID = result->GetStringField("FromUserID");
		data.testToUserID = result->GetStringField("ToUserID");
		data.testAffinityScore = result->GetStringField("AffinityScore");
// 		data.AffinityScore_ID1 
// 		data.AffinityScore_ID1
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
