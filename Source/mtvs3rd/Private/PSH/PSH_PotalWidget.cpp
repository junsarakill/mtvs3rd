// Fill out your copyright notice in the Description page of Project Settings.


#include "PSH/PSH_PotalWidget.h"
#include "PSH/PSH_Portal.h"


void UPSH_PotalWidget::NativeConstruct()
{

}

void UPSH_PotalWidget::SetHttpACtor(class APSH_Portal* Owner)
{
	Actor = Owner;
}
