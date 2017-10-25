// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LaunchProjectile(float speed);

private:
	UProjectileMovementComponent* projectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category= "Components")
	UStaticMeshComponent* collisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category= "Components")
	UParticleSystemComponent* launchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category= "Components")
	UParticleSystemComponent* impactBlast = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* explosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float destroyDelay = 10.0f;
	
};
