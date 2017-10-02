// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declarations of classes
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> projectileBlueprint;

	UTankBarrel* Barrel = nullptr;

	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchSpeed = 4000;//400 mps

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	double lastFireTime = 0;

protected:
	UTankAimingComponent* tankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* tankMovementComponent = nullptr;


public:	
	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* barrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* turretToSet);

	UFUNCTION(BlueprintCallable)
	void FireBarrel();

	


	
	
};
