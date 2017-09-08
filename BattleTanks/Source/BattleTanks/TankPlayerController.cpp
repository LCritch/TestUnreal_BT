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

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}
