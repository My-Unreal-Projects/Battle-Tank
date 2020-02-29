// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankMovementComponent;
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

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable)
	UTankBarrel* GetBarrelReference() const;
	
	UFUNCTION(BlueprintCallable)
	float GetLaunchSpeed() const;
	
private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Custom private variables
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UPROPERTY(VisibleAnywhere, Category = Firing)
	float LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000; // TODO Find sensible default

	UPROPERTY(VisibleAnywhere, Category = Firing)
	FVector HitLocation;

	// Local barrel reference for spawning projectile
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	UTankBarrel* BarrelReference;

	// Local reference of the projectile BP
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBP;
};
