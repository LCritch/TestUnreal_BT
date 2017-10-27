// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


private:

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& outHitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation)const;

	UPROPERTY(EditDefaultsOnly)
	float crosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float crosshairYLocation = .33333f;

	UPROPERTY(EditDefaultsOnly)
	float lineTraceRange = 1000000;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* aimCompRef);
	
};
