// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;
class APlayerPawnBase;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	BONUS,
};


UCLASS()
class SNAKEGAME_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf <ASnakeElementBase> SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;

	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements;

	EMovementDirection FirstMoveDirection;

	FVector HeadLocation;

	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	EMovementDirection CurrentMovementDirection; // For moving bonus

	EMovementDirection BackCondition; // For moving bonus

	FVector LastElementLocation; // For adding a new element to the end of the snake

	void CreateSnake(int ElementsNum = 1);

	void Move();

	bool CheckHead; // Only spawn if Head position deleted

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddSnakeElement();
	
	void Destruction();

	TArray<FVector> Board; 

	void DeleteBoardElement(); // When snake moves

	void AddBoardElement(FVector X); // When snake moves

	int BoardElements = 169;

	void DeleteBoardElementWhenAdd(FVector X); // When snake grows and when blocks appear 

	void SetScore(int x); 

	int Points;

	int Direction; // Moving bonus condition yes-no

	APlayerPawnBase* Pawn;


};

