// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_HttpDataTable.h"

void FPSH_HttpDataTable::PrintStruct()
{
	UE_LOG(LogTemp,Warning,TEXT("Id : %s Name : %s Age : %s Gender : %s MBTI : %s Blood : %s AffinityScore_ID1 : %d ToUserAffinityScore_1 : %f AffinityScore_ID2 : %d ToUserAffinityScore_2 : %f "),*Id, *Name , *Age, *Gender, *MBTI, *Blood, AffinityScore_ID1, ToUserAffinityScore_1, AffinityScore_ID2, ToUserAffinityScore_2);

	//UE_LOG(LogTemp, Warning, TEXT("FromUserID : %s ToUserID : %s AffinityScore : %s "), *testFromUserID, *testToUserID, *testAffinityScore);


	
	
}
