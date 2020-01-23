// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private: 

	// Custom variables
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

	// Default methods
	void BeginPlay() override;

	void Tick(float DeltaTime) override;


	// Custom methods
	ATank* GetControlledTank() const;

	void AimTowardsCrosshair(); // Start the tank moving the barrel so taht a shot wouuld hit where crosshair intersects the world

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector& LookDirection, FVector& HitLocation) const;
};
