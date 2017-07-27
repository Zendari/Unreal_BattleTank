// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "BattleTank.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
	UE_LOG(LogTemp, Warning, TEXT("DONKEY:Tank Constructor Log"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: Tank BeginPlay Log"));
}

void ATank::SetReferences(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	TankAimingComponent->Initialise(BarrelToSet, TurretToSet); //TODO see if need comment

}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (TankAimingComponent->Barrel && isReloaded)
	{
		///Spawn a projectile at the socket location
		auto SpawnLocation = TankAimingComponent->Barrel->GetSocketLocation(FName("Projectile"));
		auto SpawnRotation = TankAimingComponent->Barrel->GetSocketRotation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, FVector(SpawnLocation), FRotator(SpawnRotation));

		///Launch projectile
		Projectile->LauchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

