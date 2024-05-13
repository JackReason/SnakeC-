// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "SnakeBase.h"
#include "Food.h"
#include "Components/InputComponent.h"
#include "UserWidgetPoints.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetPoints.h"

// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90, 0, 0));
	CreateSnakeActor();
	CreateFood();
	SnakeActor->Pawn = this;
	
	if (IsValid(WidgetClass))
	{
		TextWidget = Cast<UUserWidgetPoints>(CreateWidget(GetWorld(), WidgetClass));

		if (TextWidget != nullptr)
		{
			TextWidget->AddToViewport();

		}
	}
}



// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("YYY", this, &APlayerPawnBase::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis("XXX", this, &APlayerPawnBase::HandlePlayerHorizontalInput);
}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
}

void APlayerPawnBase::CreateFood()
{
	FVector V = { 140,140,0 };
	FRotator R = { 0,0,0 };
	GetWorld()->SpawnActor<AFood>(FoodClass,V,R);

}

void APlayerPawnBase::HandlePlayerVerticalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->FirstMoveDirection!=EMovementDirection::DOWN)
		{
			SnakeActor->FirstMoveDirection = EMovementDirection::UP;
		}
		else if (value < 0 && SnakeActor->FirstMoveDirection != EMovementDirection::UP)
		{
			SnakeActor->FirstMoveDirection = EMovementDirection::DOWN;
		}
	}
}

void APlayerPawnBase::HandlePlayerHorizontalInput(float value)
{
	if (IsValid(SnakeActor))
	{

		if (value > 0 && SnakeActor->FirstMoveDirection != EMovementDirection::LEFT)
		{
			SnakeActor->FirstMoveDirection = EMovementDirection::RIGHT;
		}
		else if (value < 0 && SnakeActor->FirstMoveDirection != EMovementDirection::RIGHT)
		{
			SnakeActor->FirstMoveDirection = EMovementDirection::LEFT;
		}
	}

}

void APlayerPawnBase::WidgetScore()
{
	TextWidget->ChangeScore(SnakeActor->Points);

}

