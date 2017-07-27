// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
*
*/
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = "Collision")
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 : max downward movement +1: max upward movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreesPerSecond = 5.5;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinimumElevation = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaximumElevation = 40;
};