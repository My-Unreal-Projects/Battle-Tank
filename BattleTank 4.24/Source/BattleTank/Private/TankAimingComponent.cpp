// Copyright Cesar Molto Morilla

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	// UE_LOG(LogTemp, Warning, TEXT("Aiming Component Ticking"));
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if(!ensure(BarrelToSet)) {return;}
	Barrel = BarrelToSet;

	if(!ensure(TurretToSet)) {return;}
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity for projectile getting to the HitLocation
	bool SuggestedProjVeloc = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	
	if(!SuggestedProjVeloc) {return;}

	auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	MoveBarrelTowards(AimDirection);
	MoveTurretTowards(AimDirection);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if(!ensure(Barrel)) {return;}

	// Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotator = AimDirection.Rotation();
	auto DeltaRotator = AimDirectionRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if(!ensure(Turret)) {return;}
		
	// Work-out difference between current turret rotation and AimDirection
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimDirectionRotator = AimDirection.Rotation();
	auto DeltaRotator = AimDirectionRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	
	if(!IsReloaded) {return;}

	if(!ensure(Barrel)) {return;}
	// Spawn projectile at the barrel socket location
	FVector SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));

	if(!ensure(Projectile)) {return;}
	auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, SocketLocation, SocketRotation);

	SpawnedProjectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}




