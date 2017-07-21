// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
	auto AIControlledTank = GetAIControlledTank();
	if (!AIControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("AI Controller not found"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank: %s"), *AIControlledTank->GetName());
	}
}

ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
