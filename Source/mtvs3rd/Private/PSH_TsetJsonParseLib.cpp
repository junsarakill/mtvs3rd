// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH_TsetJsonParseLib.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"

FString UPSH_TsetJsonParseLib::JsonParse(const FString& json)
{
	// 리더기를 만들고
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(json);

	// 파싱 결과를 담을 변수 선언 . MakeShareable 스마트 포인트 관리를 위해 사용.
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject()); // 메모리 관리 
	// 해석을 한다.
	FString returnValue;
	if (FJsonSerializer::Deserialize(reader, result))
	{
		TArray<TSharedPtr<FJsonValue>> ParseDatList = result->GetArrayField(TEXT("items"));
		for (TSharedPtr<FJsonValue> data : ParseDatList)
		{
			// 책의 이름과 저자.

 			FString id = data->AsObject()->GetStringField("id");
 			FString pw = data->AsObject()->GetStringField("pw");
// 			FString authorName = data->AsObject()->GetStringField("aut_nm");
 			//returnValue.Append(FString::Printf(TEXT("BookName : %s / AuthrName : %s\n"), *bookName, *authorName));
 			returnValue.Append(FString::Printf(TEXT("id : %s \n pw : 5s"), *id, *pw));
			// 책의 이름과 저자.
// 			if (data->AsObject()->HasField("bk_nm")) // 있는지 확인
// 				int age = data->AsObject()->GetIntegerField("123");
		
		}
	}

	// 반환한다.
	return returnValue;
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
