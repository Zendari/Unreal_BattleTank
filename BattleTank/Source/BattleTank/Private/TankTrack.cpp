// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "BattleTank.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult &HitResult)
{
	DriveTracks();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::DriveTracks()
{
	//TODO clamp throttle value, so player cant change it
	auto AppliedForce = GetForwardVector() * CurrentThrottle* TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
}

void UTankTrack::ApplySidewaysForce()
{
	//Calculate slippage force
	auto TankRightVector = GetRightVector();
	auto TankVelocity = GetComponentVelocity();
	auto SlippageSpeed = FVector::DotProduct(TankVelocity, TankRightVector);
	//Work-out acceleration this frame
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime) *TankRightVector;
	//Calculate the amount of force to apply
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()*CorrectionAcceleration) / 2;  // /2 because 2 tracks on the tank
	TankRoot->AddForce(CorrectionForce);
}
