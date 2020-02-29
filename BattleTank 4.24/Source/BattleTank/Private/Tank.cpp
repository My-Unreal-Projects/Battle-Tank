// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankMovementComponent.h"
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

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Custom methods
void ATank::Fire()
{
	bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
	// IsReloaded = false; // TODO Remove this before releasing the game
	if(BarrelReference && IsReloaded && ProjectileBP)
	{
		// Spawn projectile at the barrel socket location
		FVector SocketLocation = BarrelReference->GetSocketLocation(FName("Projectile"));
		FRotator SocketRotation = BarrelReference->GetSocketRotation(FName("Projectile"));

		auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, SocketLocation, SocketRotation);

		SpawnedProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
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




