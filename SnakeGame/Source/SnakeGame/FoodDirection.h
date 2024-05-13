// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "FoodDirection.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEGAME_API AFoodDirection : public AFood
{
	GENERATED_BODY()
public:
	virtual void Interact(AActor* Intercator, bool bIsHead);
};
