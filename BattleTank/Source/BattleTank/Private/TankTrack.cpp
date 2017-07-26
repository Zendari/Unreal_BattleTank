// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "BattleTank.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//TODO clamp throttle value, so player cant change it
	auto AppliedForce = GetForwardVector() * Throttle* TrackMaxDrivingForce; 
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(AppliedForce,ForceLocation);
}


