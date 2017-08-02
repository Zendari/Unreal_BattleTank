// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"
#include "Tank.h" //Used to handle death
#include "GameFramework/Actor.h"
#include "Engine/World.h"

//Depends on movement component via path-finding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	auto PlayerPawn =(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AITank = (GetPawn());
	auto AimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();

	if (ensure(PlayerPawn)) {
		// Move towards the player
		MoveToActor(PlayerPawn, AcceptanceRadius);
		//Aim at the player
		AimingComponent->AimAt(PlayerPawn->GetActorLocation());
		//Fire 
		if(AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();  //TODO limit firing state
		}
		
	}
}


void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank)) { return; }
		//Subscribe local method to AI tank death event
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}


void ATankAIController::OnTankDeath()
{
	auto PosessedTank = GetPawn();
	if (!PosessedTank) { return; }
	PosessedTank->DetachFromControllerPendingDestroy();
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