// Copyright Cesar Molto Morilla

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward declarations
class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
*/
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup") // Does not need implementation because of its MACRO
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private: 
	// Custom variables
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	// Default methods
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	// Custom methods
	void AimTowardsCrosshair(); // Start the tank moving the barrel so taht a shot wouuld hit where crosshair intersects the world

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector& LookDirection, FVector& HitLocation) const;
};
