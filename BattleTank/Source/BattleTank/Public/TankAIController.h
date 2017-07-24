// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "CoreMinimal.h"
#include "TankAIController.generated.h"

//Forward Declarations
class ATank;
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATank* GetAIControlledTank() const;

	ATank* GetPlayerTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};