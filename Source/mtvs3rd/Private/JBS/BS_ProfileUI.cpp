// Fill out your copyright notice in the Description page of Project Settings.


#include "JBS/BS_ProfileUI.h"
#include "Components/TextBlock.h"
#include "JBS/BS_CapturePlayer.h"

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
    // 레벨에 있는 플레이어 캡처를 찾아서
    // 메시 설정
    // @@작업 여기부터
}
