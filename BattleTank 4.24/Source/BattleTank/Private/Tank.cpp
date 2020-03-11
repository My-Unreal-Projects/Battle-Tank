// Copyright Cesar Molto Morilla

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Custom methods
void ATank::Fire()
{
	if(!ensure(BarrelReference && ProjectileBP)) {return;}

	bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
	// IsReloaded = false; // TODO Remove this before releasing the game
	
	if(!IsReloaded) {return;}

	// Spawn projectile at the barrel socket location
	FVector SocketLocation = BarrelReference->GetSocketLocation(FName("Projectile"));
	FRotator SocketRotation = BarrelReference->GetSocketRotation(FName("Projectile"));

	auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, SocketLocation, SocketRotation);

	SpawnedProjectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void ATank::SetHitLocation(FVector HitLocationToSet)
{
	HitLocation = HitLocationToSet;
}

FVector ATank::GetHitLocation() const
{
	return HitLocation;
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	BarrelReference = BarrelToSet;
}

UTankBarrel* ATank::GetBarrelReference() const
{
	return BarrelReference;	
}

float ATank::GetLaunchSpeed() const
{
	return LaunchSpeed;
}




