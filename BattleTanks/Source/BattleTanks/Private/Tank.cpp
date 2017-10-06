// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


void ATank::FireBarrel()
{

		bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;

		if (Barrel && isReloaded)
		{

			//else spawn projectile
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				projectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);

			Projectile->LaunchProjectile(launchSpeed);
			lastFireTime = FPlatformTime::Seconds();
		}
}