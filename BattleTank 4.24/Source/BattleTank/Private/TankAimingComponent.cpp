// Copyright Cesar Molto Morilla

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// So that the first shot is after the initial reload
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(BulletsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if(!BarrelToSet) {return;}
	Barrel = BarrelToSet;

	if(!TurretToSet) {return;}
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity for projectile getting to the HitLocation
	bool SuggestedProjVeloc = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	
	if(!SuggestedProjVeloc) {return;}

	AimDirection = OutLaunchVelocity.GetSafeNormal();

	MoveBarrelTowards(AimDirection);
	MoveTurretTowards(AimDirection);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if(!Barrel) {return;}

	// Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotator = AimDirection.Rotation();
	auto DeltaRotator = AimDirectionRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if(!Turret) {return;}
		
	// Work-out difference between current turret rotation and AimDirection
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimDirectionRotator = AimDirection.Rotation();
	auto DeltaRotator = AimDirectionRotator - TurretRotator;

	if(FMath::Abs(DeltaRotator.Yaw) < 180)
		Turret->Rotate(DeltaRotator.Yaw);
	else // Avoid rotate the long way
		Turret->Rotate(-DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{	
	if(FiringState != EFiringState::Reloading && FiringState != EFiringState::OutOfAmmo)
	{
		if(!Barrel) {return;}
		// Spawn projectile at the barrel socket location
		FVector SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));

		if(!Projectile) {return;}
		auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, SocketLocation, SocketRotation);

		SpawnedProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();

		BulletsLeft--;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if(!Barrel) {return false;}
	
	FVector BarrelDirection = Barrel->GetForwardVector();

	return !AimDirection.Equals(BarrelDirection, 0.05);
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetBulletsLeft() const
{
	return BulletsLeft;
}




