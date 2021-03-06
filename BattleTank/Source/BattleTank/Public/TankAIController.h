// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "CoreMinimal.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	//How close will the AI tank stop in front of player
	UPROPERTY(EditDefaultsOnly,Category="Setup")
	float AcceptanceRadius=8000;

public:

	UFUNCTION()
	void OnTankDeath();

	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn);

	virtual void Tick(float DeltaSeconds) override;

};