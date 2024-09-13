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

 	int To_User1; //- ���� ����
 	int To_User2;//- ���� ����
// 
 	int LikeScore1; //- ������
 	int LikeScore2;// - �������� �̵� �亯


	  void PrintStruct();
 };


