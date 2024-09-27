// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_LobbyGameModeBase.h"
#include "Camera/PlayerCameraManager.h"

void APSH_LobbyGameModeBase::PostLogin(APlayerController *NewPlayer) 
{
    Super::PostLogin(NewPlayer);
    //     �α��� ���� ���� ȣ��˴ϴ�.PlayerController ���� ���ø�����Ʈ�Ǵ� �Լ� ȣ���� �ϱ⿡ ������ ù ��°
    //         ����Դϴ�.�������Ʈ�� OnPostLogin �� �����Ͽ� �ΰ� ������ �߰��� �� �ֽ��ϴ�.

    playerCount++;
    if (playerCount >= 4)
    {
        FTimerHandle f;
        GetWorld()->GetTimerManager().SetTimer(f, [&]() {Travel(); }, 5, false);
      
//         NewPlayer->PlayerCameraManager->StartCameraFade(1, 1, 100, FColor::Black);
//         MRPC_StartFade();
    }
    UE_LOG(LogTemp, Warning, TEXT("Player Count %d"), playerCount);
    
}
void APSH_LobbyGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    
}
void APSH_LobbyGameModeBase::Travel()
{
    GetWorld()->ServerTravel(FString("/Game/Main/MainMap?listen"));
}
void APSH_LobbyGameModeBase::MRPC_StartFade_Implementation()
{
    APlayerCameraManager* cam = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
    cam->StartCameraFade(1,1,100,FColor::Black);
}