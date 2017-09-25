// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
//Holds Tank Barrel Properties and Elevate Method 
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , hideCategories = ("Collision"))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float degreesPerSecond);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreesPerSecond = 20;
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float minElevationDegrees = 0;

	UPROPERTY(EditAnywhere, Category = Setup)
	float maxElevationDegrees = 40;
	
};
