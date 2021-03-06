// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!aimingComponent) { return; }
	FoundAimingComponent(aimingComponent);
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }// check if possessing
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!aimingComponent) { return; }

	FVector hitLocation; // out parameter

	bool bGotHitLocation = GetSightRayHitLocation(hitLocation);

	if (bGotHitLocation) // if linetrace returns true
	{

		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s") , *hitLocation.ToString());
		aimingComponent->AimAt(hitLocation);
	}
}

// Get world location of linetrace from crosshair location, returns true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation)const
{
	//find crosshair position via getting Half of X&Y coords on screen
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	auto screenLocation = FVector2D(viewportSizeX * crosshairXLocation, viewportSizeY * crosshairYLocation);
	

	//deproject screen pos of crosshair to world direction
	FVector lookDirection;
	if (GetLookDirection(screenLocation,lookDirection))
	{
		//line trace forward look direction, see what we hit
		return GetLookVectorHitLocation(lookDirection,outHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);	
}

bool ATankPlayerController::GetLookVectorHitLocation (FVector lookDirection, FVector& hitLocation)const
{
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility)
	)

	{
		hitLocation = hitResult.Location;
		return true;
	}

	hitLocation = FVector(0);
	return false;
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
		Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto possessedTank = Cast<ATank>(InPawn);
		if (!possessedTank) { return; }
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Died!"));
	StartSpectatingOnly();
}