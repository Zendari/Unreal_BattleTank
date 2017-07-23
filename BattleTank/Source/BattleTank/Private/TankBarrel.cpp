// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"


void UTankBarrel::Elevate(float DegreesPerSecond)
{
	//Move barrel the right amount this frame
	//With a max speed and frame time
	UE_LOG(LogTemp, Warning, TEXT("Elevate at %f"),DegreesPerSecond);
}
