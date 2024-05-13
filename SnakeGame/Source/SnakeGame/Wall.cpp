// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
AWall::AWall()
{
 	
}

void AWall::Interact(AActor* Interactor, bool IsHead)
{
	auto Snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(Snake))
	{
		Snake->SetActorTickInterval(10);
		Snake->Destruction();

	}
}

