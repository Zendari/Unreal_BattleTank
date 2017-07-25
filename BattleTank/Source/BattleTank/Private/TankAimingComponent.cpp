// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Tank.h"
#include "TankTurret.h"
#include "BattleTank.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO does it need to Tick
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
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
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		//Getting the normal first, actual aim direction
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName(); //Used for logging
		MoveBarrelToward(AimDirection);
		MoveTurretToward(AimDirection);
	}
	//If not solution, getting out of here
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	//Make the difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);//Elevating the barrel

}

void UTankAimingComponent::MoveTurretToward(FVector AimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotator - TurretRotator;
	if (FMath::Abs(DeltaRotation.Yaw) < 180)
	{
		Turret->SetTurretRotation(DeltaRotation.Yaw);
	}
	else
	{
		Turret->SetTurretRotation(-DeltaRotation.Yaw);
	}
}

/*Logging Section*/
/*if(bHaveAimSolution){
auto time = GetWorld()->GetTimeSeconds();
UE_LOG(LogTemp, Warning, TEXT("%f: Solution found"), time);
}
else {
UE_LOG(LogTemp, Error, TEXT("No Aim solution found"));
}*/