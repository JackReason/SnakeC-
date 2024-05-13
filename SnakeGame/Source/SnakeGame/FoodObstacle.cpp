// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodObstacle.h"
#include "SnakeBase.h"

void AFoodObstacle::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->SetActorTickInterval(10);
			Snake->Destruction();
		}

	}
	
}
