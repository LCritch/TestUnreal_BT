// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: Throttle: %f"), *Name, Throttle);

	//TODO clamp throttle value so player can't go over -1/+1

	auto forceApplied = GetForwardVector() * Throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, forceLocation);

}


