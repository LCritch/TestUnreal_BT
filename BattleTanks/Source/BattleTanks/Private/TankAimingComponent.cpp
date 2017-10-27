// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initalise(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	Barrel = barrelToSet;
	Turret = turretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (roundsLeft <= 0)
	{
		firingState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds)
	{
		firingState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		firingState = EFiringState::Aiming;
	}
	else
	{
		firingState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return firingState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return roundsLeft;
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!Barrel) { return false; }
	auto barrelForward = Barrel->GetForwardVector();
	return !barrelForward.Equals(aimDirection, 0.01);
}

void UTankAimingComponent::AimAt(FVector hitLocation)
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
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	/* get current aimlocation, adjust rotation of barrel towards that location by aim at or lerp rotator
	* move barrel correctly per frame
	* give max elevation speed and current frame time
	*/
	if (!Barrel ||!Turret) { return; }

	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = AimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);

	//always turn via the shortest distance
	if (FMath::Abs(deltaRotator.Yaw) < 180)
	{
		Turret->Rotate(deltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-deltaRotator.Yaw);
	}

}

void UTankAimingComponent::FireBarrel()
{

		if (firingState == EFiringState::Locked||firingState == EFiringState::Aiming)
		{
			//else spawn projectile
			if (!Barrel) { return; }
			if (!projectileBlueprint) { return; }
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				projectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);

			lastFireTime = FPlatformTime::Seconds();
			Projectile->LaunchProjectile(launchSpeed);
			roundsLeft--;
		}
}


