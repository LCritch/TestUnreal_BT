// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


private:

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& outHitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation)const;

	UPROPERTY(EditAnywhere)
	float crosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float crosshairYLocation = .33333f;

	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000;
	
};
