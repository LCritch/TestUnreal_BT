// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	Barrel = barrelToSet;
	auto barrelOwnerName = Barrel->GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Barrel Set"),*barrelOwnerName);
}


void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!Barrel) { return; }

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
		auto tankName = GetOwner()->GetName();
		MoveBarrelTowards(aimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"),*tankName, *aimDirection.ToString());
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	/* get current aimlocation, adjust rotation of barrel towards that location by aim at or lerp rotator
	* move barrel correctly per frame
	* give max elevation speed and current frame time
	*/

	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	Barrel->Elevate(5); //todo remove basic number

}

