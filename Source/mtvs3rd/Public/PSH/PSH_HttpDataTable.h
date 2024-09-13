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

	// XXX 미사용
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ToUserAffinityScore_1; // 내가 선택한 상대 1의 호감도  Key -> ToUserID

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	  int otherUserID2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	  float syncPercentID2;

	// XXX 미사용
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 int ToUserAffinityScore_2;

	  void PrintStruct();

	// JBS 추가 생성자
	FPSH_HttpDataTable() {}
	
	FPSH_HttpDataTable(int Id, FString Name, int Age, FString Gender
					, FString MBTI, FString Blood
					, int otherUserID1, float syncPercentID1
					, int otherUserID2, float syncPercentID2
					, float ToUserAffinityScore_1 = 0.f
					, float ToUserAffinityScore_2 = 0.f)
		: Id(Id), Name(Name), Age(Age), Gender(Gender)
		, MBTI(MBTI), Blood(Blood)
		, otherUserID1(otherUserID1), syncPercentID1(syncPercentID1)
		, otherUserID2(otherUserID2), syncPercentID2(syncPercentID2) {}
 };


