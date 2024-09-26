// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/MiniGameMissionWidget.h"
#include "JYS/MiniGameWidgetActor.h"

void UMiniGameMissionWidget::NativeConstruct()
{
}

void UMiniGameMissionWidget::SetOwner(AMiniGameWidgetActor* actor)
{
	owner = actor;
}
