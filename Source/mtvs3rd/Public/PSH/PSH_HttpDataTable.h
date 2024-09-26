// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PSH_HttpDataTable.generated.h"


USTRUCT(Atomic,BlueprintType) // ���� ��� ������
 struct FPSH_HttpDataTable : public FTableRowBase
 {
	GENERATED_USTRUCT_BODY()
 public:

	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 int Id;
	// int Id;
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 FString Name; // �������� ������
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 int Age;  // 2�� ���� // ��ư ������ 1�� �������� 9�Ѿ�� 0���� �ʱ�ȭ
	// int Age;  // 2�� ���� // ��ư ������ 1�� �������� 9�Ѿ�� 0���� �ʱ�ȭ

	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 FString Gender; // ���� 2�� ����
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 FString MBTI; // ����
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 FString Blood; // ����

	
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	  int otherUserID1; //  Key -> FromUserID
	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	  float syncPercentID1; // ��ũ���� Key -> AffinityScore

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	  int otherUserID2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	  float syncPercentID2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
 	int To_User1; //- ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
 	int To_User2;//- ���� ����
// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
 	int LikeScore1; //- ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Values")
 	int LikeScore2;// - �������� �̵� �亯


	  void PrintStruct();

	// JBS �߰� ������
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


