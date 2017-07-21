// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	
	///Logging the PlayerControlled Tank found by AI
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI could not find PlayerTank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI found PlayerTank: %s"), *PlayerTank->GetName());
	}
	
}

ATank* ATankAIController::GetAIControlledTank() const
{
	///Return the tanks controlled by AI
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	///Getting Player Pawn
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {return nullptr;}
	return Cast<ATank>(PlayerPawn);
}



///Logging Section
/* Logging which tank is controlled by AI
	auto AIControlledTank=GetAIControlledTank();
	if (!AIControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("AI Controller not found"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank: %s"), *AIControlledTank->GetName());
		}*/