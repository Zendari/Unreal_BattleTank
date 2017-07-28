// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "CoreMinimal.h"
#include "TankAIController.generated.h"

//Forward Declarations

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	//How close will the AI tank stop in front of player
	float AcceptanceRadius=3000;
};