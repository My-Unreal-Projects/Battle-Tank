// Fill out your copyright notice in the Description page of Project Settings.

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

	// No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

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
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	// Setting aming component barrel reference
	TankAimingComponent->SetBarrelReference(BarrelToSet);

	// Setting tank local barrel reference
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	// auto Time = GetWorld()->GetTimeSeconds();
	// UE_LOG(LogTemp, Warning, TEXT("%f: Firing!"), Time);

	bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	if(Barrel && IsReloaded)
	{
		// Spawn projectile at the barrel socket location
		FVector SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));

		auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, SocketLocation, SocketRotation);

		SpawnedProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}




