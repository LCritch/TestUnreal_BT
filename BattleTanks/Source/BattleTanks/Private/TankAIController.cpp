// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledTank = GetPawn();

	if (!playerTank && controlledTank) { return; }
	
		//move towards player
		MoveToActor(playerTank, acceptanceRadius);

		//aim towards the player
		auto aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
		aimingComponent->AimAt(playerTank->GetActorLocation());

		if (aimingComponent->GetFiringState() == EFiringState::Locked)
		{
			aimingComponent->FireBarrel();
		}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto possessedTank = Cast<ATank>(InPawn);
		if (!possessedTank) { return; }
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}



