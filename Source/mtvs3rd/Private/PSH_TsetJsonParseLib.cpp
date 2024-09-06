// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH_TsetJsonParseLib.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "PSH/PSH_HttpActor.h"
#include "PSH/PSH_HttpDataTable.h"

void UPSH_TsetJsonParseLib::JsonParse(const FString& json, FPSH_HttpDataTable& data)
{
	// 리더기를 만들고
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);

	// 파싱 결과를 담을 변수 선언 . MakeShareable 스마트 포인트 관리를 위해 사용.
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject()); // 메모리 관리 
	// 해석을 한다.
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

	// 반환한다.
	//return newRow;
}

FString UPSH_TsetJsonParseLib::MakeJson(const TMap<FString, FString> source)
{
	// source를 jsonObject형식으로 만들고
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());

	for (TPair<FString, FString> pair : source)
	{
		jsonObject->SetStringField(pair.Key, pair.Value);
	}

	// Writer를 만들어서 jsonObject를 인코딩해서 
	FString json;
	TSharedRef<TJsonWriter<TCHAR>> writer = TJsonWriterFactory<TCHAR>::Create(&json);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef(), writer);

	//반환
	return json;
}
