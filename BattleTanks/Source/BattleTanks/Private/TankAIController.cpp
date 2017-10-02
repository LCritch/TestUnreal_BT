// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto controlledTank = Cast<ATank>(GetPawn());
	if (playerTank)
	{
		//move towards player
		MoveToActor(playerTank, acceptanceRadius);

		//aim towards the player
		controlledTank->AimAt(playerTank->GetActorLocation());

		//fire if ready
		controlledTank->FireBarrel();//TODO Don't fire per frame
	}
}



