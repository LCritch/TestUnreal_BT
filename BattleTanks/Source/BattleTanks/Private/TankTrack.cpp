// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{

	auto forceApplied = GetForwardVector() * Throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);

}


