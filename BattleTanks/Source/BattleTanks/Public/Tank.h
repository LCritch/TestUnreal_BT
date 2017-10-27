// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category  = "Setup")
	int32 startingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category  = "Health")
	int32 currentHealth;

public:	
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent, class AController * EventInstigator,AActor * DamageCauser)override;
	
	UFUNCTION(BlueprintPure, Category= "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;
	
};
