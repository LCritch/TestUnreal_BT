// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this,&UTankTrack::OnHit);
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	currentThrottle = 0;
	
}

void UTankTrack::ApplySidewaysForce()
{
	//calculate slip speed, work out required acceleration this frame to correct. Calculate and apply sideways force.
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();

	//calculate and apply sideways force
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2;// divide by two due to two tracks

	tankRoot->AddForce(correctionForce);
}


void UTankTrack::DriveTrack()
{
	auto forceApplied = GetForwardVector() * currentThrottle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

void UTankTrack::SetThrottle(float Throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + Throttle, -1, 1);
}


