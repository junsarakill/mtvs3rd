// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PSH_HttpDataTable.generated.h"


USTRUCT(Atomic,BlueprintType) // 최초 통신 데이터
 struct FPSH_HttpDataTable : public FTableRowBase
 {
	GENERATED_USTRUCT_BODY()
 public:

	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 int Id;
	// int Id;
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 FString Name; // 랜덤으로 지어짐
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 int Age;  // 2개 선택 // 버튼 누르면 1씩 더해지고 9넘어가면 0으로 초기화
	// int Age;  // 2개 선택 // 버튼 누르면 1씩 더해지고 9넘어가면 0으로 초기화

	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 FString Gender; // 성별 2개 선택
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 FString MBTI; // 선택
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 FString Blood; // 선택

	
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	  int otherUserID1; //  Key -> FromUserID
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	  float syncPercentID1; // 싱크로율 Key -> AffinityScore

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	  int otherUserID2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	  float syncPercentID2;

 	int To_User1; //- 누구 에게
 	int To_User2;//- 누구 에게
// 
 	int LikeScore1; //- 설문지
 	int LikeScore2;// - 스테이지 이동 답변


	  void PrintStruct();
 };


