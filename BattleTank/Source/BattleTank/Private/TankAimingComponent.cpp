// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Tank.h"
#include "BattleTank.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate OutLauchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity  //<-Actual calculation of the projectile speed (OutLaunchVelocity)
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //Getting the normal first, actual aim direction
		auto TankName = GetOwner()->GetName(); //Used for logging
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s "),*TankName, *AimDirection.ToString());
		//TODO MoveBarrel();
	}
	//If not solution, getting out of here
	return;
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	//Make the difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator =  AimAsRotator - BarrelRotator;
	Barrel->Elevate(5);
	//TODO Not use magic number
}
