// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"
#include "MyFoodSpeed.h"
#include "FoodDirection.h"
#include "FoodObstacle.h"

// Game's board
AFood::AFood()
{
	Score = 0;
}


void AFood::Interact(AActor* Interactor, bool IsHead)
{
	if (IsHead) 
	{
		Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			SetDefaults();
			
			TArray<FVector>& mas = Snake->Board;
			int Num = Snake->BoardElements;
			
			Score = 10;
			Snake->SetScore(Score);
		
			
			Snake->AddSnakeElement();
	
			int choice = rand()%5;
			//int choice = 0;
		
			switch (choice)

			{
			case 0:
				CreateFood(0,Num,mas);   // Obstacle
				CreateFood(3, Num, mas);
				break;
			case 1:
				CreateFood(1,Num,mas);  // Opposite direction
				break;
			case 2:
				CreateFood(2,Num,mas); // Speed
				break;
			default:
				CreateFood(3,Num,mas);  // Ordinary food
				break;
			}
		}

	}
	Destroy();
}


void AFood::CreateFood( int choice, int NumElem, TArray<FVector>& Mas)
{
	int i = rand() % NumElem;
	FRotator R = { 0,0,0 };
	FVector FoodLocation = Mas[i];
	switch (choice)
	{
	case 0:
		GetWorld()->SpawnActor<AFoodObstacle>(FoodToObstacle, FoodLocation, R);
		Snake->DeleteBoardElementWhenAdd(FoodLocation);
		break;
	case 1:
		GetWorld()->SpawnActor<AFoodDirection>(FoodToDirection, FoodLocation, R);
		break;
	case 2:
		GetWorld()->SpawnActor<AMyFoodSpeed>(FoodSpeed, FoodLocation, R);
		break;
	case 3:
		GetWorld()->SpawnActor<AFood>(FoodToSpawn, FoodLocation, R);
		break;
	}
}


void AFood::SetDefaults()
{
	Snake->SetActorTickInterval(0.6);
	Snake->Direction = 1;
}


