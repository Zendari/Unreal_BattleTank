// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "BattleTank.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 
}

void UTankAimingComponent::BeginPlay()
{
	//So that first fire is after first reload
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("Aim Comp tick"));
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTime) 
	{
		FiringState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForwardVector = Barrel->GetForwardVector();
	return !BarrelForwardVector.Equals(AimDirection, 0.01);	 //Vectors are equals
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

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
	    AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName(); //Used for logging
		MoveBarrelToward(AimDirection);
		MoveTurretToward(AimDirection);
	}
	//If not solution, getting out of here
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	if (!ensure(Barrel)) { return; }
	//Make the difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);//Elevating the barrel

}

void UTankAimingComponent::MoveTurretToward(FVector AimDirection)
{
	if (!ensure(Turret)) { return; }
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

void UTankAimingComponent::Fire()
{

	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		///Spawn a projectile at the socket location
		auto SpawnLocation = this->Barrel->GetSocketLocation(FName("Projectile"));
		auto SpawnRotation = this->Barrel->GetSocketRotation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, FVector(SpawnLocation), FRotator(SpawnRotation));

		///Launch projectile
		Projectile->LauchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		RoundsLeft--;
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