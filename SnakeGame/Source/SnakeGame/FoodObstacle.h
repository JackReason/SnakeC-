// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "FoodObstacle.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEGAME_API AFoodObstacle : public AFood
{
	GENERATED_BODY()
	
	virtual void Interact(AActor* Interactor, bool bIsHead);
};
