// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"
#include "PlayerPawnBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	FirstMoveDirection = EMovementDirection::DOWN;
	Direction = 1;
	CurrentMovementDirection = EMovementDirection::DOWN;
	BackCondition = EMovementDirection::BONUS;
	CheckHead = 1;

}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	CreateSnake();
	
	// init game board
	float MaxX = 420.f;
	float MinX = -420.f;
	float MaxY = 420.f;
	float MinY = -420.f;
	for (float x = MinX; x <= MaxX; x += ElementSize)
	{
		for (float y = MinY; y <= MaxY; y += ElementSize)
		{
			FVector temp = { x,y,0 };
			Board.Add(temp);
		}

	}

}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CheckHead)                               // Only spawn if Head position is deleted 
	{
		Move();
	}

}

void ASnakeBase::CreateSnake(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{


		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NeSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NeSnakeElem->SnakeOwner = this;
		int32 ElemIndex = SnakeElements.Add(NeSnakeElem);
		if (ElemIndex == 0)
		{
			NeSnakeElem->SetFirstElementType();
		}
	}
		
}

void ASnakeBase::Move()
{
	CheckHead = 0;                               // Only spawn if Head position is deleted
	FVector MovementVector(ForceInitToZero);
	FVector OppositeVector(ForceInitToZero);
	

	switch (FirstMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		OppositeVector.X -= ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		OppositeVector.X += ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y -= ElementSize;
		OppositeVector.Y += ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y += ElementSize;
		OppositeVector.Y -= ElementSize;
		break;

	}


	
	auto HeadElement = SnakeElements[0];
    HeadLocation = HeadElement->GetActorLocation();

	
	// Either opposite or not

	if (Direction == 1 || FirstMoveDirection == CurrentMovementDirection)
	{
		if (BackCondition == FirstMoveDirection)
		{
			SnakeElements[0]->AddActorWorldOffset(OppositeVector);
			DeleteBoardElement();                                     // Delete new Head position
		}
		else
		{
			SnakeElements[0]->AddActorWorldOffset(MovementVector);
			DeleteBoardElement();                                    // Delete new Head position
			CurrentMovementDirection = FirstMoveDirection;
			BackCondition = EMovementDirection::BONUS;
		}
		
	}
	else
	{
		SnakeElements[0]->AddActorWorldOffset(OppositeVector);
		DeleteBoardElement();                                        // Delete new Head position
		CurrentMovementDirection = EMovementDirection::BONUS;
		BackCondition = FirstMoveDirection;
	}

	// moving the rest

	for (int i = 1; i < SnakeElements.Num(); i++)
	{
		if (i == SnakeElements.Num() - 1)                          // For adding a new element to the end of the snake
		{
			auto LastElement = SnakeElements[i];
			LastElementLocation = LastElement->GetActorLocation(); 
			AddBoardElement(LastElementLocation);                  // New position when tail moved
		}

		auto NextElement = SnakeElements[i];
		FVector NextElementLocation = NextElement->GetActorLocation();
		NextElement->SetActorLocation(HeadLocation);
		HeadLocation = NextElementLocation;
		

	}
	
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = (ElemIndex == 0);
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}
	}

}

void ASnakeBase::AddSnakeElement()
{
	FRotator R = { 0,0,0 };
	ASnakeElementBase* LastSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, LastElementLocation, R);
	LastSnakeElement->SnakeOwner = this;
	SnakeElements.Add(LastSnakeElement);
	DeleteBoardElementWhenAdd(LastElementLocation);

}

void ASnakeBase::Destruction()
{
	for (int i = 0; i < SnakeElements.Num(); i++)
	{
		auto Temp = SnakeElements[i];
		Temp->Destroy();
		Destroy();
	}
}

void ASnakeBase::DeleteBoardElement()
{
	auto E = SnakeElements[0];
	FVector temp = E->GetActorLocation();
	Board.Remove(temp);
	BoardElements--;
	CheckHead = 1;                                         // Only spawn if Head position is deleted

}

void ASnakeBase::AddBoardElement(FVector X)
{
	Board.Add(X);
	BoardElements++;
	
}

void ASnakeBase::DeleteBoardElementWhenAdd(FVector X)
{
	Board.Remove(X);
	BoardElements--;

}

void ASnakeBase::SetScore(int x)
{
	Points += x;
	Pawn->WidgetScore();
}

