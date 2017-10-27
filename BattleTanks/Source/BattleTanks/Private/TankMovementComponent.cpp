// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initalise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{

	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

#pragma region
void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!leftTrack && rightTrack) { return; }

	leftTrack->SetThrottle(Throw);
	rightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!leftTrack && rightTrack) { return; }

	leftTrack->SetThrottle(Throw);
	rightTrack->SetThrottle(-Throw);
}
#pragma endregion intended L/R Throttle passed through to the relevant track

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call super as functionality is being overrided
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto aiForwardIntention = MoveVelocity.GetSafeNormal();

	auto forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);
	IntendMoveForward(forwardThrow);

	auto rightThrow = FVector::CrossProduct(tankForward,aiForwardIntention).Z;
	IntendTurnRight(rightThrow);

}
