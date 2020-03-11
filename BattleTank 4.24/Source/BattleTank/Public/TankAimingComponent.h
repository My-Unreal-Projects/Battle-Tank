// Copyright Cesar Molto Morilla

#pragma once

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declarations
class UTankBarrel; 
class UTankTurret;

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Constructor
	UTankAimingComponent(); // Sets default values for this component's properties

	// Custom methods
	UFUNCTION(BlueprintCallable, Category = "Aiming")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Aiming")
	void AimAt(FVector HitLocation, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	void MoveTurretTowards(FVector AimDirection);	

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000;
};
