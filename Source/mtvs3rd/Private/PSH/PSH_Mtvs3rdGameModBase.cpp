// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_Mtvs3rdGameModBase.h"
#include "PSH_TsetJsonParseLib.h"
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
	//PlayerStateClass = ABS_PlayerState::StaticClass();
}

void APSH_Mtvs3rdGameModBase::BeginPlay()
{
	Super::BeginPlay();
	
	Gi = Cast<UPSH_GameInstance>(GetGameInstance());

// 	auto * pc = GetWorld()->GetFirstPlayerController();
// 	if (pc)
// 	{
// 		playerState = Cast<ABS_PlayerState>(pc->PlayerState);
// 	}
	

	
}

void APSH_Mtvs3rdGameModBase::PreLogin(const FString &Options, const FString &Address, const FUniqueNetIdRepl &UniqueId, FString &ErrorMessage)
{
    Super::PreLogin(Options,Address,UniqueId,ErrorMessage);
    //     ������ ���� �õ����� �÷��̾ ���� �Ǵ� �ź��մϴ�
//         .ErrorMessage �� ������ �ƴ� ��Ʈ���� �Է��ϸ� Login �Լ��� �����ϵ��� ����ϴ�.PreLogin �� Login �� ȣ��Ǹ�,
//         �����ϴ� �÷��̾ ���� �������� �ٿ�ε��ؾ� �ϴ� ��� �ð��� ���� �������� Login �� ȣ��� ���� �ֽ��ϴ�.
}

void APSH_Mtvs3rdGameModBase::PostLogin(APlayerController *NewPlayer) 
{
    Super::PostLogin(NewPlayer);

     Gi = Cast<UPSH_GameInstance>(GetGameInstance());

    // ���� ���� �÷��̾�� GI�� �ִ� �����͸� �־��ְ� �ʹ�.
    auto *pc = NewPlayer;

    if (pc)
    {
        playerState = Cast<ABS_PlayerState>(pc->PlayerState);
        if (playerState != nullptr)
        {
			Gi->StartDataReQestJson();
            playerState->SetPlayerData(Gi->GetStartData());
        }
    }
   
	
    //     �α��� ���� ���� ȣ��˴ϴ�.PlayerController ���� ���ø�����Ʈ�Ǵ� �Լ� ȣ���� �ϱ⿡ ������ ù ��°
//         ����Դϴ�.�������Ʈ�� OnPostLogin �� �����Ͽ� �ΰ� ������ �߰��� �� �ֽ��ϴ�.

}

void APSH_Mtvs3rdGameModBase::SetData(FPSH_HttpDataTable Data)
{
	PlayerData = Data;
}

void APSH_Mtvs3rdGameModBase::LastChoice(int FromId, int ToId) // 4�� �Ҹ���. ���� ����. // ���� , ������
{

	// FromID�� To ID �� ������ �ڿ�
	// From ID �� TO ID , TO ID �� From ID�� ���� ���� ¦�� ã�´�.
	// 10 / 20 �ϰ�� 20 / 10 �� ������ ����.

	ChoiceNum.Add(FromId,ToId); // ChoiceNum[FromId] = ToId;

	LastChoiceNum++; // �Լ� ���� Ƚ�� üũ

	if (LastChoiceNum < playerCount) // �׽�Ʈ ���� �÷��̾� �� ���� 2
	{
		return;
	}

	ChekChoice();
	
	// for���� �����鼭 Toid
	// �̸� ����� ���� ��
	// �� id �� ��
	
	// ������ ���� UI
	

	// Ʋ���� ���� UI
	//

}

FPSH_HttpDataTable APSH_Mtvs3rdGameModBase::GetData(int num)
{
	return Gi->GetData(num);
}

void APSH_Mtvs3rdGameModBase::ChekChoice() // ����� 2������ �����Ǿ� ���� 4���� �� UI ��� ������� �ϴ��� �� �𸣰ھ ���� ����
{

		for (auto& ID : ChoiceNum)  // ��ü Ȯ���� �߱� ������ 3���� �˻� �� �ʿ䰡 ����.
		{
			const int* foundkey = ChoiceNum.FindKey(ID.Key); // value�� �̿��� key�� ã�´�. key�� �ִٸ� ��ġ�� ���� Ȯ��.

			if (foundkey != nullptr)
			{
// 				if(!Gi)
// 				return;

				ChoiceActor->SetPlayerName(Gi->GetData(ID.Key).Name); // 1
				PRINTLOG(TEXT("ID.Key"));
// 				ChoiceActor->GetPlayerName(Gi->GetData(*foundkey).Name); // 2
// 				PRINTLOG(TEXT("foundkey"));
			}
			
// 			if (ChoiceNum[i] == 0) // �÷��̾ ���� ���߰ų� �÷��̾ �ƴ�
// 			{
// 				continue;
// 			}
// 			else
// 			{		// �÷��̾� ��ȣ = 3 / 1
// 					// 1 2 3 4  /1     arr[1]
// 				if ( i == ChoiceNum[ChoiceNum[i]]) // ���� 1���� ������ �ڽ��� �����ߴ���
// 				{
// 					ChoiceWidget->SuccessChoice();
// 				}
// 				else
// 				{
// 					ChoiceWidget->FailChoice();
// 				}
// 			}
		}
	
}

void APSH_Mtvs3rdGameModBase::SetLastWdiget(class UPSH_LastChoiceWidget* widget)
{
	ChoiceWidget = widget;
}

void APSH_Mtvs3rdGameModBase::SetActor(class APSH_LastChoiceActor *Actor) 
{
	ChoiceActor = Actor;
    if (ChoiceActor)
	UE_LOG(LogTemp,Warning,TEXT("APSH_LastChoiceActor : %s"),*ChoiceActor->GetName());
}
