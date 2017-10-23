// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

protected:
	//How close AI Tank can get to player
	UPROPERTY(EditDefaultsOnly, Category= "Setup")//consider EditDefaultsOnly
	float acceptanceRadius = 3000;

};
