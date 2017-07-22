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
		GetControlledTank()->AimAt(HitLocation);
			//TODO Tell the controlledTank to aim at this point
	}
}

//Get world location of line-trace through crosshair, return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation=FVector2D(ViewportSizeX*CrosshairXLocation,ViewportSizeY*CrosshairYLocation); //<- Actual crosshair position
	
	//De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation,LookDirection))
	{
		//Line trace along that look direction and see what we hit (up to max range, LineTraceRange)
		GetLookVectorHitLocation(LookDirection,OutHitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection (FVector2D ScreenLocation,FVector& LookDirection) const
{
	FVector CameraWorldLocation;//Is discarded
	return DeprojectScreenPositionToWorld( //Return where is the player looking at on a XYZ axis of unit 1
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection,FVector& OutHitLocation) const {
	
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation =StartLocation+(LookDirection*LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel( //Then we line trace on the XYZ Axis with a range of LineTraceRange
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)) 
	{
		OutHitLocation = HitResult.Location; //Getting the location of the LineTrace
		return true;
	}
	OutHitLocation = FVector(0); 
	return false;
}