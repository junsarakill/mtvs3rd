// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_ProfileUI.h"
#include "Components/TextBlock.h"
#include <JBS/BS_CapturePlayer.h>
#include <Kismet/GameplayStatics.h>


ABS_CapturePlayer *UBS_ProfileUI::GetCapturePlayer()
{
    // 이미 알면 가져오기
    if(cp) return cp;
    // 월드에서 찾기
    else
    {
        CP = Cast<ABS_CapturePlayer>(
            UGameplayStatics::GetActorOfClass(GetWorld(), ABS_CapturePlayer::StaticClass()));
        if(cp) return cp;
        // 없으면 생성하기
        else
        {
            CP = GetWorld()->SpawnActor<ABS_CapturePlayer>(cpPrefab, FTransform(FRotator(0,0,0), FVector(0,0,-2000), FVector(1,1,1)));
            if(cp) return cp;
        }
    }

    return nullptr;
}

void UBS_ProfileUI::SetCapturePlayer(ABS_CapturePlayer *value)
{
    cp = value;
}

void UBS_ProfileUI::SetName(FString value) 
{
    NameText->SetText(FText::FromString(value));
}

void UBS_ProfileUI::SetSyncPercent(int32 value)
{
    // "value %"
    FString str = FString::Printf(TEXT("%d %%"), value);
    SyncPercentText->SetText(FText::FromString(str));

}

void UBS_ProfileUI::SetCapturePlayer(EPlayerType type)
{
    check(CP);
    // 메시 설정
    CP->SetMesh(type);

    // GEngine->AddOnScreenDebugMessage(-1,3.f, FColor::Green, FString::Printf(TEXT("type: %s"), *UEnum::GetValueAsString(type)));
}
