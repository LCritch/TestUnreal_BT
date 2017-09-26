// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PC not possessing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PC possessing:  %s"), *(controlledTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("PC BeginPlay"));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector hitLocation; // out parameter

	if (GetSightRayHitLocation(hitLocation)) // if linetrace returns true
	{

		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s") , *hitLocation.ToString());
		GetControlledTank()->AimAt(hitLocation);
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
		GetLookVectorHitLocation(lookDirection,outHitLocation);
	}



	//outHitLocation = FVector(1.0);
	return true;
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