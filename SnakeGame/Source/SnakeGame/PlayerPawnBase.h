// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawnBase.generated.h"

class UCameraComponent;
class ASnakeBase;
class AFood;
class UUserWidgetPoints;

UCLASS()
class SNAKEGAME_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* PawnCamera;

	UPROPERTY(BlueprintReadWrite)
	ASnakeBase* SnakeActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeBase> SnakeActorClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodClass;

	//widget

	UPROPERTY(EditAnywhere, Category = "Class Types")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
     UUserWidgetPoints* TextWidget;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateSnakeActor();

	void CreateFood();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void HandlePlayerVerticalInput(float value);
	UFUNCTION()
	void HandlePlayerHorizontalInput(float value);

	void WidgetScore();

};
