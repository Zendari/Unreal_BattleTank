// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UTankTrack();

	virtual void BeginPlay() override;
	
	void ApplySidewaysForce();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult &HitResult);

public :
	//Set a throttle between +1 and -1
	UFUNCTION(BlueprintCallable,Category="Input")
	void SetThrottle(float Throttle);

	void DriveTracks();
	
	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 420000; //Tank weight 42 000 kg, Assuming it'll move 10m/s
	
	float CurrentThrottle = 0;
};
