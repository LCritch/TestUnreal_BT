// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

	//calculate slip speed, work out required acceleration this frame to correct. Calculate and apply sideways force.
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();

	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2;// divide by two due to two tracks

	tankRoot->AddForce(correctionForce);

}

void UTankTrack::SetThrottle(float Throttle)
{

	auto forceApplied = GetForwardVector() * Throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);

}


