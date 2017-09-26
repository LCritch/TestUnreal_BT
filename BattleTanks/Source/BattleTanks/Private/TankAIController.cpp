// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto playerTank = GetPlayerTank();
	if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIC Found Player:  %s"), *(playerTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("AIC BeginPlay"));


}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//move towards player

		//aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

ATank* ATankAIController::GetPlayerTank()const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerPawn) { return nullptr; }

	return Cast<ATank>(playerPawn);
}



