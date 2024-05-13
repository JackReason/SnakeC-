// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFoodSpeed.h"
#include "SnakeBase.h"

void AMyFoodSpeed::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			TArray<FVector>& mas = Snake->Board;
			int Num = Snake->BoardElements;
			Snake->AddSnakeElement();
			Snake->SetActorTickInterval(0.3);
			CreateFood(3, Num, mas);
			Score = 20;
			Snake->SetScore(Score);
			Destroy();
		}

	}
	if (bIsHead == 0)
	{
		//Destroy();
		//CreateFood(3);
	}
}