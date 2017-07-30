// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "BattleTank.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//Calculate slippage force
	auto TankRightVector = GetRightVector();
	auto TankVelocity = GetComponentVelocity();
	auto SlippageSpeed = FVector::DotProduct(TankVelocity, TankRightVector);
	//Work-out acceleration this frame
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime) *TankRightVector;
	//Calculate the amount of force to apply
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()*CorrectionAcceleration) / 2;  // /2 because 2 tracks on the tank
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	//TODO clamp throttle value, so player cant change it
	auto AppliedForce = GetForwardVector() * Throttle* TrackMaxDrivingForce; 
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(AppliedForce,ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult &HitResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Log of OnHit"));
}
