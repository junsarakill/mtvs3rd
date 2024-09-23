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
    //     서버에 접근 시도중인 플레이어를 수락 또는 거부합니다
//         .ErrorMessage 에 공백이 아닌 스트링을 입력하면 Login 함수가 실패하도록 만듭니다.PreLogin 은 Login 전 호출되며,
//         참가하는 플레이어가 게임 콘텐츠를 다운로드해야 하는 경우 시간이 한참 지나서야 Login 이 호출될 수도 있습니다.
}

void APSH_Mtvs3rdGameModBase::PostLogin(APlayerController *NewPlayer) 
{
    Super::PostLogin(NewPlayer);

     Gi = Cast<UPSH_GameInstance>(GetGameInstance());

    // 새로 들어온 플레이어에게 GI에 있는 데이터를 넣어주고 싶다.
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
   
	
    //     로그인 성공 이후 호출됩니다.PlayerController 에서 리플리케이트되는 함수 호출을 하기에 안전한 첫 번째
//         장소입니다.블루프린트로 OnPostLogin 을 구현하여 부가 로직을 추가할 수 있습니다.

}

void APSH_Mtvs3rdGameModBase::SetData(FPSH_HttpDataTable Data)
{
	PlayerData = Data;
}

void APSH_Mtvs3rdGameModBase::LastChoice(int FromId, int ToId) // 4번 불린다. 갱신 가능. // 누가 , 누구를
{

	// FromID와 To ID 를 저장한 뒤에
	// From ID 와 TO ID , TO ID 와 From ID가 서로 같은 짝을 찾는다.
	// 10 / 20 일경우 20 / 10 과 같으면 맞음.

	ChoiceNum.Add(FromId,ToId); // ChoiceNum[FromId] = ToId;

	LastChoiceNum++; // 함수 실행 횟수 체크

	if (LastChoiceNum < playerCount) // 테스트 현재 플레이어 수 현재 2
	{
		return;
	}

	ChekChoice();
	
	// for문을 돌리면서 Toid
	// 미리 만들어 놓고 비교
	// 각 id 를 비교
	
	// 같으면 성공 UI
	

	// 틀리면 실패 UI
	//

}

FPSH_HttpDataTable APSH_Mtvs3rdGameModBase::GetData(int num)
{
	return Gi->GetData(num);
}

void APSH_Mtvs3rdGameModBase::ChekChoice() // 현재는 2명으로 구현되어 있음 4명일 때 UI 어떻게 보여줘야 하는지 잘 모르겠어서 추후 수정
{

		for (auto& ID : ChoiceNum)  // 전체 확인을 했기 때문에 3명을 검사 할 필요가 없다.
		{
			const int* foundkey = ChoiceNum.FindKey(ID.Key); // value를 이용해 key를 찾는다. key가 있다면 일치된 존재 확인.

			if (foundkey != nullptr)
			{
// 				if(!Gi)
// 				return;

				ChoiceActor->SetPlayerName(Gi->GetData(ID.Key).Name); // 1
				PRINTLOG(TEXT("ID.Key"));
// 				ChoiceActor->GetPlayerName(Gi->GetData(*foundkey).Name); // 2
// 				PRINTLOG(TEXT("foundkey"));
			}
			
// 			if (ChoiceNum[i] == 0) // 플레이어를 선택 안했거나 플레이어가 아님
// 			{
// 				continue;
// 			}
// 			else
// 			{		// 플레이어 번호 = 3 / 1
// 					// 1 2 3 4  /1     arr[1]
// 				if ( i == ChoiceNum[ChoiceNum[i]]) // 남자 1번과 누군가 자신을 선택했는지
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
