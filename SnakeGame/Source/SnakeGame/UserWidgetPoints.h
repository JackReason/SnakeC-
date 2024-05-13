// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetPoints.generated.h"

/**
 * 
 */
class APlayerPawnBase;

UCLASS()
class SNAKEGAME_API UUserWidgetPoints : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Score;

	virtual void NativeConstruct() override;

	APlayerPawnBase* Pawn;

public:
	void ChangeScore(int score);
	
};
