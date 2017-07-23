// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move barrel the right amount this frame
	//With a max speed and frame time
	auto ClampedSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = ClampedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation= FMath::Clamp<float>(RawNewElevation, MinimumElevation, MaximumElevation);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
