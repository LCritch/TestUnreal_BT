// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledTank = GetPawn();

	if (!ensure(playerTank && controlledTank)) { return; }
	
		//move towards player
		MoveToActor(playerTank, acceptanceRadius);

		//aim towards the player
		auto aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
		aimingComponent->AimAt(playerTank->GetActorLocation());

		//todo fix firing
		//controlledTank->FireBarrel(); //TODO Don't fire per frame
	
	
}



