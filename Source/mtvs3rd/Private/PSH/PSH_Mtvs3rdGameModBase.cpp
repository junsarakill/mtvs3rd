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
//     서버에 접근 시도중인 플레이어를 수락 또는 거부합니다
//     ErrorMessage 에 공백이 아닌 스트링을 입력하면 Login 함수가 실패하도록 만듭니다.PreLogin 은 Login 전 호출되며,
//     참가하는 플레이어가 게임 콘텐츠를 다운로드해야 하는 경우 시간이 한참 지나서야 Login 이 호출될 수도 있습니다.
}

// 로그인 성공 이후 호출됩니다.PlayerController 에서 리플리케이트되는 함수 호출을 하기에 안전한 첫 번째 장소입니다.
// 블루프린트로 OnPostLogin 을 구현하여 부가 로직을 추가할 수 있습니다.

void APSH_Mtvs3rdGameModBase::PostLogin(APlayerController *NewPlayer) 
{
    Super::PostLogin(NewPlayer);
	
	playerCount++;
	//Gi->PlayerData.Id = playerCount;
	playerState = Cast<ABS_PlayerState>(NewPlayer->PlayerState);
	playerState->id = playerCount;

}

void APSH_Mtvs3rdGameModBase::LastChoice(int FromId, int ToId) // 4번 불린다. 갱신 가능. // 누가 , 누구를
{
	ChoiceNum.Add(FromId,ToId); // ChoiceNum[FromId] = ToId;
	LastChoiceNum++; // 함수 실행 횟수 체크
	PRINTLOG(TEXT("FromId : %d , ToId : %d"),FromId , ToId);
	if (LastChoiceNum < playerCount) // 테스트 현재 플레이어 수 현재 2
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

void APSH_Mtvs3rdGameModBase::ChekChoice() // 현재는 2명으로 구현되어 있음 4명일 때 UI 어떻게 보여줘야 하는지 잘 모르겠어서 추후 수정
{

//  1 : 4
//  2 : 3
//  3 : 1
//  4 : 1
// 	FString* Ptr7 = FruitMap.Find(7); // 키를 이용해 찾은뒤에 벨류를 반환
// 	// *Ptr7 == "Pineapple"
// 
// 	const int32* KeyMangoPtr = FruitMap.FindKey(TEXT("Mango")); // 벨류를 이용해 키를 찾는다..
// 	// *KeyMangoPtr   == 5

	for (auto& ID : ChoiceNum)  // 전체 확인을 했기 때문에 3명을 검사 할 필요가 없다.
	{
		const int* foundkey1 = ChoiceNum.Find(ID.Value); // value를 이용해 key를 찾는다. key가 있다면 일치된 존재 확인.

		if (foundkey1 != nullptr)
		{
			// 키를 찾고 키의 값이 자신의 값과 같은지 확인.
			if (ID.Key == *foundkey1)
			{
				ChoiceActor->SetPlayerName(Gi->GetData(ID.Key).Name, Gi->GetData(ID.Value).Name); // 1
				// 매칭이 된순간 지워버린다. = foundkey 가 nullptr이 될거다.
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
		LastChoice(1, 4);  // 1 영철 2 옥순 3 영수 4 영숙
		LastChoice(4, 1);
	}
}