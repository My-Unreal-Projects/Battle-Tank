// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();

    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player controller not possesing a tank"));
    }

    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player controller possesing %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
    // UE_LOG(LogTemp, Warning, TEXT("Player Ticking."));
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank()) { return; }

    FVector HitLocation; // Out parameter

    if(GetSightRayHitLocation(HitLocation)) // Has "side-efect", is going to line trace
    {
        // UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
        // TODO Tell controlled tank to aim at this point
    }
}

// Get world location of linetrace through crosshair, true if hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

    UE_LOG(LogTemp, Warning, TEXT("Screen location: %s"), *ScreenLocation.ToString());

    // "De-project" the screen position of the crosshair to a world direction
    // Line-trace along that look direction, and see what we hit (up to max range)
    return true;
}

