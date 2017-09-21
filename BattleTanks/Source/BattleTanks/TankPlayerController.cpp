// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
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
	//UE_LOG(LogTemp, Warning, TEXT("PC Tick"));
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

		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s") , *hitLocation.ToString());

		//get world location of linetrace through crosshair
		//if linetrace hits landscape
		//tell tank to aim at hit point
	}
}

// Get world location of linetrace from crosshair location, returns true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation)const
{
	//find crosshair position via getting Half of X&Y coords on screen
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	auto screenLocation = FVector2D(viewportSizeX * crosshairXLocation, viewportSizeY * crosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *screenLocation.ToString());

	//deproject screen pos of crosshair to world direction
	FVector lookDirection;
	if (GetLookDirection(screenLocation,lookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *lookDirection.ToString());
	}

	//line trace forward look direction, see what we hit

	outHitLocation = FVector(1.0);
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);	
}