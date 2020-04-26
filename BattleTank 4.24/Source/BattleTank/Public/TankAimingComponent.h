// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declarations
class UTankTurret;
class UTankBarrel; 
class AProjectile;
class AActor;
class UGameplayStatics;

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	// Constructor
	UTankAimingComponent(); // Sets default values for this component's properties

	void BeginPlay() override;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Aiming")
	FVector AimDirection;

	// UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<AProjectile> Projectile; 

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000;

	UPROPERTY(VisibleAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 2;

	UPROPERTY(VisibleAnywhere, Category = "Firing")
	float LastFireTime = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 BulletsLeft = 200;

public:	
	// Custom methods
	UFUNCTION(BlueprintCallable, Category = "Aiming")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet, TSubclassOf<AProjectile> ProjectileToSet, float ReloadTimeToSet);

	UFUNCTION(BlueprintCallable, Category = "Aiming")
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetBulletsLeft() const;

	UFUNCTION(BlueprintCallable, Category = "Control")
	bool IsBarrelMoving();

	EFiringState GetFiringState() const;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	void MoveBarrelTowards(FVector AimDirection);

	void MoveTurretTowards(FVector AimDirection);	
};
