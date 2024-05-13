// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Food.generated.h"

class ASnakeBase;
class MyFoodSpeed;

UCLASS()
class SNAKEGAME_API AFood : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

protected:
	ASnakeBase* Snake;

public:	
	// Called every frame
    

	virtual void Interact(AActor* Interactor, bool IsHead) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodToSpawn;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodSpeed;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodToDirection;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodToObstacle;

	virtual void CreateFood( int choice, int NumElem, TArray<FVector>& V);
	
	void SetDefaults();

	int Score;

};
