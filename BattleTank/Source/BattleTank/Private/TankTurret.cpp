// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::SetTurretRotation(float RelativeSpeed)
{
	auto ClampedSpeedRotation = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = ClampedSpeedRotation*MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	auto YawRotationToDo = RelativeRotation.Yaw+RotationChange;
	auto Rotation = FMath::Clamp<float>(YawRotationToDo, 0, 360);
	SetRelativeRotation(FRotator(0, YawRotationToDo, 0));
}

