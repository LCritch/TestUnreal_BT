// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declarations of classes
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectileBlueprint;

	UTankBarrel* Barrel = nullptr; //TODO Remove


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	double lastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launchSpeed = 4000;//400 mps

public:	

	UFUNCTION(BlueprintCallable)
	void FireBarrel();
	
	
};
