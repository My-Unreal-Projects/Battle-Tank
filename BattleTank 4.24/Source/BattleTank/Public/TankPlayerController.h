// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

private_subobject: 

	// PRIVATE VARIABLES
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3;

	// PRIVATE DEFAULT METHODS
	void BeginPlay() override;

	void Tick(float DeltaTime) override;


	// PRIVATE CUSTOM METHODS
	ATank* GetControlledTank() const;

	// Start the tank moving the barrel so taht a shot wouuld hit where
	// crosshair intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;
};
