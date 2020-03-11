// Copyright Cesar Molto Morilla

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

/*%%%%%%%%%%%%%% Default methods %%%%%%%%%%%%%%%%*/
// Called once at the start of the game or when Spawned
void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Getting aiming component from controlled tank
    auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>(); 
    if(!ensure(AimingComponent)) {return;}
    FoundAimingComponent(AimingComponent);
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

// Custom methods
ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!ensure(GetControlledTank())) {return;}

    FVector HitLocation; // Out parameter

    if(!GetSightRayHitLocation(HitLocation)) {return;} // Has "side-efect", is going to line trace
    
    GetControlledTank()->SetHitLocation(HitLocation);
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

    if(!(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))) {return false;}

    // Set hit location
    HitLocation = HitResult.Location;
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // To be discarded
    if(!DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection)) {return false;}

    return true; 
}


