// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetPoints.h"
#include "Components/TextBlock.h"
#include "PlayerPawnBase.h"


void UUserWidgetPoints::NativeConstruct()
{
	Score->SetText(FText::AsNumber(0));
}

void UUserWidgetPoints::ChangeScore(int score)
{
	Score->SetText(FText::AsNumber(score));
}

