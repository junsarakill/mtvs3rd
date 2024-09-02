// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PSH_TsetJsonParseLib.generated.h"

/**
 * 
 */

UCLASS()
class MTVS3RD_API UPSH_TsetJsonParseLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	
	static FString JsonParse(const FString& json);

	static FString MakeJson(const TMap<FString, FString> source);

};
