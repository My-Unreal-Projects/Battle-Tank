// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Custom methods
	UFUNCTION(BlueprintCallable)
	void Fire();

	void SetHitLocation(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	FVector GetHitLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable)
	UTankBarrel* GetBarrelReference() const;
	
	UFUNCTION(BlueprintCallable)
	float GetLaunchSpeed() const;
	
private:
	// Sets default values for this pawn's properties
	ATank();

	// Custom private variables
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(VisibleAnywhere, Category = "Firing")
	float LastFireTime = 3;

	// TODO Remove once Fire is completely moved to AimingComponent class
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000;

	UPROPERTY(VisibleAnywhere, Category = "Firing")
	FVector HitLocation;

	// Local barrel reference for spawning projectile
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UTankBarrel* BarrelReference; // TODO Remove this reference

	// Local reference of the projectile BP
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBP;
};
