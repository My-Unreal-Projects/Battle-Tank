// Copyright Cesar Molto Morilla

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"


// Default methods
// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if(!InPawn) {return;}
    auto PossessedTank = Cast<ATank>(InPawn);

    if(!PossessedTank) {return;}

    PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
}

// Custom methods
void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetPawn()) {return;} // e.g if not possesing
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>(); 
    if(!AimingComponent) {return;}

    FVector PlayerTankLocation = GetPawn()->GetActorLocation();
    FVector HitLocation; // Out parameter

    if(!GetSightRayHitLocation(HitLocation)) // Has "side-efect", is going to line trace
    {
        // UE_LOG(LogTemp, Warning, TEXT("Aiming solution not found!"));
    } 
    else
        AimingComponent->AimAt(HitLocation); // TODO Fix aiming solution to the floor

    // UE_LOG(LogTemp, Warning, TEXT("Difference: %f"), (HitLocation - FVector(PlayerTankLocation.X, PlayerTankLocation.Y, HitLocation.Z)).Size());
}

// Get world location of linetrace through crosshair, true if hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

    // "De-project" the screen position of the crosshair to a world direction
    FVector LookDirection;
    if(!GetLookDirection(ScreenLocation, LookDirection)) {return false;}
    // Line-trace along that look direction, and see what we hit (up to max range)
    if(!GetLookVectorHitLocation(LookDirection, HitLocation)) {return false;}

    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;

    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if(!GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1)) {return false;}

    // UE_LOG(LogTemp, Warning, TEXT("Hit result actor: %s"), *HitResult.Actor->GetName());
    // Set hit location
    HitLocation = HitResult.Location;

    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // To be discarded
    if(!DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection)) {return false;}

    // UE_LOG(LogTemp, Warning, TEXT("Look Direction Rotator: %s"), *LookDirection.Rotation().ToString());

    // if(LookDirection.Z < 0) // TOCHANGE Change this temporal fix to the aiming, this prevents the tank from trying to aim at itself
    //    LookDirection = FVector(LookDirection.X, LookDirection.Y, 0);

    return true; 
}

void ATankPlayerController::OnPossessedTankDeath()
{
    StartSpectatingOnly();
    PossessedTankDead();
}


