// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward Declarations
class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	//Start the tank moving the barrel so that a shot would hit
	//where the crosshair intersects the world
	void AimTowardsCrosshair();

	//Return an out parameter, true if hits landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

protected:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

public:

	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5; //Because it is 50% right from the top-left corner

	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.33333;//Because it is 33% down from the middle-top

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;
};