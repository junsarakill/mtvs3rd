// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_LobbyGameModeBase.h"
#include "Camera/PlayerCameraManager.h"

void APSH_LobbyGameModeBase::PostLogin(APlayerController *NewPlayer) 
{
    Super::PostLogin(NewPlayer);
    //     로그인 성공 이후 호출됩니다.PlayerController 에서 리플리케이트되는 함수 호출을 하기에 안전한 첫 번째
    //         장소입니다.블루프린트로 OnPostLogin 을 구현하여 부가 로직을 추가할 수 있습니다.

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