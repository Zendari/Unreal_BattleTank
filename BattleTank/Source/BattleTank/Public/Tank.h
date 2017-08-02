// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTank);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	ATank();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; //Initialised in begin play

public:
	//UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FTank OnDeath;

	//Called by engine when it takes a hit
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	//Return current health as a percentage of starting health between 0 and 1
	UFUNCTION(BlueprintPure, Category="Health")
	float GetHealtPercent() const;

};