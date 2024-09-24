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

}



void APSH_Mtvs3rdGameModBase::LastChoice(int FromId, int ToId) // 4�� �Ҹ���. ���� ����. // ���� , ������
{

	ChoiceNum.Add(FromId,ToId); // ChoiceNum[FromId] = ToId;
	LastChoiceNum++; // �Լ� ���� Ƚ�� üũ

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

	for (auto& ID : ChoiceNum)  // ��ü Ȯ���� �߱� ������ 3���� �˻� �� �ʿ䰡 ����.
	{
		const int* foundkey = ChoiceNum.FindKey(ID.Key); // value�� �̿��� key�� ã�´�. key�� �ִٸ� ��ġ�� ���� Ȯ��.

		if (foundkey != nullptr)
		{
			ChoiceActor->SetPlayerName(Gi->GetData(ID.Key).Name); // 1
			PRINTLOG(TEXT("ID.Key"));
		}
	}
	
}

void APSH_Mtvs3rdGameModBase::SetActor(class APSH_LastChoiceActor *Actor) 
{
	ChoiceActor = Actor;
    if (ChoiceActor)
	UE_LOG(LogTemp,Warning,TEXT("APSH_LastChoiceActor : %s"),*ChoiceActor->GetName());
}
