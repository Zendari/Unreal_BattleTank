// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("Player Controller not found"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerControlled Tank: %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation; //Out Parameter
	if (GetSightRayHitLocation(HitLocation)) //Is going to line-trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction :%s"), *HitLocation.ToString());
			//Tell the controlledTank to aim at this point
	}
}

//Get world location of line-trace through crosshair, return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation=FVector2D(ViewportSizeX*CrosshairXLocation,ViewportSizeY*CrosshairYLocation); //<- Actual crosshair position
	
	return false;
}