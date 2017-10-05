// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aim state
UENUM()
enum class EFiringState: uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initalise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

	void AimAt(FVector hitLocation, float launchSpeed);


protected:
	UPROPERTY(BlueprintReadOnly, Category= "State")
	EFiringState firingState = EFiringState::Aiming;


private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector aimDirection);


		
	
};
