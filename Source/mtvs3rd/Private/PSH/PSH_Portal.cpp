// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_Portal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "JBS/BS_Utility.h"
#include "PSH/PSH_PotalWidget.h"
#include "JBS/BS_VRPlayer.h"
#include "mtvs3rdCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "JBS/BS_PlayerState.h"
#include "PSH/PSH_GameInstance.h"
#include "mtvs3rd.h"
#include "PSH/PSH_Mtvs3rdGameModBase.h"

// Sets default values
APSH_Portal::APSH_Portal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	widget->SetupAttachment(RootComponent);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	mesh->SetupAttachment(RootComponent);
    bReplicates = true;
}

// Called when the game starts or when spawned
void APSH_Portal::BeginPlay()
{
	Super::BeginPlay();

	mesh->OnComponentBeginOverlap.AddDynamic(this, &APSH_Portal::OnComponentBeginOverlap);

	if (widget)
	{
		PotalWidget = Cast<UPSH_PotalWidget>(widget->GetWidget());
		if (PotalWidget)
		{
			PotalWidget->SetHttpACtor(this);
			UE_LOG(LogTemp, Warning, TEXT("HttpWidget : %s"), *PotalWidget->GetClass()->GetName());
		}
	}

	SetPortal();

	if (bisEndPotal)
	{
		mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		widget->SetVisibility(false);
	}
}

// Called every frame
void APSH_Portal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APSH_Portal::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	player = Cast<ABS_VRPlayer>(OtherActor);
	
	// 서버에서 배열에 들어간 애를 제외하고 배열에 들어가지 않은 애들이 왔을때 playerCount를 증가 시키고 싶다.
	if (player)
	{          
            if (HasAuthority()) // 서버에서
            {
                if (PlayerArray.Find(player) != INDEX_NONE) // 배열에 있다면
                {
                    for (auto *cehk : PlayerArray)
                    {
                        UE_LOG(LogTemp, Warning, TEXT("Acotr : %s"), *cehk->GetName());
                       
					}

                    return;
				}
				else // 배열에 없다면
				{
					// jbs 수정
// 					auto playerData = player->GetPlayerState<ABS_PlayerState>()->GetPlayerData(); // 상대의 데이터를 가져옴
// 					PlayerDataArray.Add(playerData); // 플레이어 스테이트의 구조체.
//                                       
					PlayerArray.Add(player);
					PlayerCount++;
					OnRep_PlayerPotal();
					
				}
            }
	}
}
void APSH_Portal::OnRep_PlayerPotal()
{ 
	PotalWidget->SetPlayerCount(PlayerCount); 
}
void APSH_Portal::Setvisilbe(bool chek)
{
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APSH_Portal::SetPortal()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagetName,EndPotal);
}

void APSH_Portal::GoPotal()
{
	// 맨처음 플레이어를 기준으로 호감도 높은 ID를 판별
//     if (!PlayerDataArray.IsEmpty())
//     {
//         if (PlayerDataArray[0].syncPercentID1 >= PlayerDataArray[0].syncPercentID2) // 호감도 비교.
//         {
//             SetMeshPlayerID = PlayerDataArray[0].otherUserID1; // 높은 호감도 ID
//         }
//         else
//         {
//             SetMeshPlayerID = PlayerDataArray[0].otherUserID2; // 높은 호감도 ID
//         }
// 	}
//     
//     // 베타에 설문 추가
//     for (auto PlayerChek : PlayerArray) // 플레이어 의 배열
//     {
//         auto playerDataChek = PlayerChek->GetMyPS()->GetPlayerData();
//         if (SetMeshPlayerID == playerDataChek.Id) // 가장 호감도가 높은 ID와 ID를 비교
//         {
// 			//PlayerArray[0]-> // 0번을 기준으로 찾았기 때문에 0번의 매쉬를 변경
//             //PlayerChek->   // 0번 기준 호감도가 가장 높은 플레이어의 매쉬를 변경 
// 			break;
// 		}
//         playerDataChek.PrintStruct();
//     }

    SRPC_GoPotal();
}

void APSH_Portal::SRPC_GoPotal_Implementation() 
{
    for (auto *playerList : PlayerArray)
    {
        playerList->SetActorLocation(EndPotal[0]->GetActorLocation());
	}

	if (TagetName == TEXT("EndPotal"))
    {
       MRPC_GoPotal();
	   auto * Gm = Cast<APSH_Mtvs3rdGameModBase>(GetWorld()->GetAuthGameMode());
	   Gm->Test();
	  
    }
}

void APSH_Portal::MRPC_GoPotal_Implementation() 
{
    if (TagetName == TEXT("EndPotal"))
    {
        auto *state = Cast<ABS_PlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
        state->SetIsFinalSelect(true);
		PRINTLOG(TEXT("EndPotalOn"));
    }
}

void APSH_Portal::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APSH_Portal,PlayerCount);
}


// 플레이어의 호감도가 가장 높은 그룹을 짝지어 매쉬를 바꾸고 싶다.
// 메쉬는 플레이어, 호감도는 게임 인스턴스 또는 플레이어 스테이트.
// 4명의 호감도를 비교하는 방법.
// 플레이어 ID 와 플레이어를 