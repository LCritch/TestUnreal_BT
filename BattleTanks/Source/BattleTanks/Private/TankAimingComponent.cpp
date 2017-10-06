// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initalise(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	Barrel = barrelToSet;
	Turret = turretToSet;
}


void UTankAimingComponent::AimAt(FVector hitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector outLaunchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the out launch velocity
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,0,0,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	/* get current aimlocation, adjust rotation of barrel towards that location by aim at or lerp rotator
	* move barrel correctly per frame
	* give max elevation speed and current frame time
	*/
	if (!ensure(Barrel) ||!ensure (Turret)) { return; }

	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
	Turret->Rotate(deltaRotator.Yaw);

}

