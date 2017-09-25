// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* barrelToSet);

	// TODO finish implementation of turretreference
	void SetTurretReference();

protected:


public:	

	void AimAt(FVector hitLocation, float launchSpeed);


private:
	UTankBarrel* Barrel = nullptr;

	void MoveBarrelTowards(FVector aimDirection);
		
	
};
