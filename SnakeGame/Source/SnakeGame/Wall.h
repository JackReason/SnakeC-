// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Wall.generated.h"

UCLASS()
class SNAKEGAME_API AWall : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWall();

protected:
	
public:	

	virtual void Interact(AActor* Interactor, bool IsHead) override;
	


};
