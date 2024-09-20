// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_LobbyGameModeBase.h"

void APSH_LobbyGameModeBase::PostLogin(APlayerController *NewPlayer) 
{
    Super::PostLogin(NewPlayer);
    //     �α��� ���� ���� ȣ��˴ϴ�.PlayerController ���� ���ø�����Ʈ�Ǵ� �Լ� ȣ���� �ϱ⿡ ������ ù ��°
    //         ����Դϴ�.�������Ʈ�� OnPostLogin �� �����Ͽ� �ΰ� ������ �߰��� �� �ֽ��ϴ�.

    playerCount++;
    if (playerCount >= 4)
    {
        GetWorld()->ServerTravel(FString("/Game/Main/MainMap?listen"));
    }
    UE_LOG(LogTemp, Warning, TEXT("Player Count %d"), playerCount);
}
