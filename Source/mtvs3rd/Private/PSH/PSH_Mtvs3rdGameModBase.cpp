// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "PSH/PSH_HttpDataTable.h"
#include "HttpModule.h"
#include "Kismet/GameplayStatics.h"
#include "JBS/BS_PlayerState.h"
#include "PSH/PSH_GameInstance.h"
#include "PSH/PSH_LastChoiceWidget.h"
#include "PSH/PSH_LastChoiceActor.h"
#include "mtvs3rd.h"


APSH_Mtvs3rdGameModBase::APSH_Mtvs3rdGameModBase()
{

}

void APSH_Mtvs3rdGameModBase::BeginPlay()
{
	Super::BeginPlay();
	
	Gi = Cast<UPSH_GameInstance>(GetGameInstance());

// 	APlayerCameraManager* cam = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
// 	cam->StartCameraFade(1, 0, 5, FColor::Black);

}

void APSH_Mtvs3rdGameModBase::PreLogin(const FString &Options, const FString &Address, const FUniqueNetIdRepl &UniqueId, FString &ErrorMessage)
{
    Super::PreLogin(Options,Address,UniqueId,ErrorMessage);
//     ������ ���� �õ����� �÷��̾ ���� �Ǵ� �ź��մϴ�
//     ErrorMessage �� ������ �ƴ� ��Ʈ���� �Է��ϸ� Login �Լ��� �����ϵ��� ����ϴ�.PreLogin �� Login �� ȣ��Ǹ�,
//     �����ϴ� �÷��̾ ���� �������� �ٿ�ε��ؾ� �ϴ� ��� �ð��� ���� �������� Login �� ȣ��� ���� �ֽ��ϴ�.
}

// �α��� ���� ���� ȣ��˴ϴ�.PlayerController ���� ���ø�����Ʈ�Ǵ� �Լ� ȣ���� �ϱ⿡ ������ ù ��° ����Դϴ�.
// �������Ʈ�� OnPostLogin �� �����Ͽ� �ΰ� ������ �߰��� �� �ֽ��ϴ�.

void APSH_Mtvs3rdGameModBase::PostLogin(APlayerController *NewPlayer) 
{
    Super::PostLogin(NewPlayer);
	
	playerCount++;
	//Gi->PlayerData.Id = playerCount;
	playerState = Cast<ABS_PlayerState>(NewPlayer->PlayerState);
	playerState->id = playerCount;

}

void APSH_Mtvs3rdGameModBase::LastChoice(int FromId, int ToId) // 4�� �Ҹ���. ���� ����. // ���� , ������
{
	ChoiceNum.Add(FromId,ToId); // ChoiceNum[FromId] = ToId;
	LastChoiceNum++; // �Լ� ���� Ƚ�� üũ
	PRINTLOG(TEXT("FromId : %d , ToId : %d"),FromId , ToId);
	if (LastChoiceNum < playerCount) // �׽�Ʈ ���� �÷��̾� �� ���� 2
	{
		return;
	}

	ChekChoice();
}

void APSH_Mtvs3rdGameModBase::SetData(FPSH_HttpDataTable Data)
{
	PlayerData = Data;
}

FPSH_HttpDataTable APSH_Mtvs3rdGameModBase::GetData(int num)
{
	return Gi->GetData(num);
}

void APSH_Mtvs3rdGameModBase::ChekChoice() // ����� 2������ �����Ǿ� ���� 4���� �� UI ��� ������� �ϴ��� �� �𸣰ھ ���� ����
{

//  1 : 4
//  2 : 3
//  3 : 1
//  4 : 1
// 	FString* Ptr7 = FruitMap.Find(7); // Ű�� �̿��� ã���ڿ� ������ ��ȯ
// 	// *Ptr7 == "Pineapple"
// 
// 	const int32* KeyMangoPtr = FruitMap.FindKey(TEXT("Mango")); // ������ �̿��� Ű�� ã�´�..
// 	// *KeyMangoPtr   == 5

	for (auto& ID : ChoiceNum)  // ��ü Ȯ���� �߱� ������ 3���� �˻� �� �ʿ䰡 ����.
	{
		const int* foundkey1 = ChoiceNum.Find(ID.Value); // value�� �̿��� key�� ã�´�. key�� �ִٸ� ��ġ�� ���� Ȯ��.

		if (foundkey1 != nullptr)
		{
			// Ű�� ã�� Ű�� ���� �ڽ��� ���� ������ Ȯ��.
			if (ID.Key == *foundkey1)
			{
				ChoiceActor->SetPlayerName(Gi->GetData(ID.Key).Name, Gi->GetData(ID.Value).Name); // 1
				// ��Ī�� �ȼ��� ����������. = foundkey �� nullptr�� �ɰŴ�.
// 				ChoiceNum.Remove(ID.Key);
// 				ChoiceNum.Remove(ID.Value);
			}
			else
			{
				PRINTLOG(TEXT("FoundKey == nullptr"));
			}
		}
		else
		{
			PRINTLOG(TEXT("FoundKey == nullptr"));
		}
	}
	
}

void APSH_Mtvs3rdGameModBase::SetActor(class APSH_LastChoiceActor *Actor) 
{
	ChoiceActor = Actor;
	if (ChoiceActor)
	{

// 		PRINTLOG(TEXT("APSH_LastChoiceActor : %s"),*ChoiceActor->GetName());
// 	 		FTimerHandle f;
//  		
// 		GetWorld()->GetTimerManager().SetTimer(f,this,&APSH_Mtvs3rdGameModBase::Test, 5, false);
	}
}
void APSH_Mtvs3rdGameModBase::Test()
{
	if (ChoiceActor)
	{
		LastChoice(1, 4);  // 1 ��ö 2 ���� 3 ���� 4 ����
		LastChoice(4, 1);
	}
}