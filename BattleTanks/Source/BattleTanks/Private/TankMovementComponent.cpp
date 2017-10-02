// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initalise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	if (!leftTrackToSet || !rightTrackToSet){return;}

	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!leftTrack || !rightTrack) { return; }

	leftTrack->SetThrottle(Throw);
	rightTrack->SetThrottle(Throw);

	//TODO Prevent speed multiplying due to stick & trigger/ bumper input

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call super as functionality is being overrided
	auto tankName = GetOwner()->GetName();
	auto moveVelocityString = MoveVelocity.ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *tankName, *moveVelocityString)
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!leftTrack || !rightTrack) { return; }

	leftTrack->SetThrottle(Throw);
	rightTrack->SetThrottle(-Throw);

	//TODO Prevent speed multiplying due to stick & trigger/ bumper input
}

