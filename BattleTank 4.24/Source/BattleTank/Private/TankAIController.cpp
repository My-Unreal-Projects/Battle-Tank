// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

// Called once at the beginning of the game
void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto PlayerTank = GetPlayerTank();

    if(!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI can't find the player tank."));
    }

    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI found the player tank: %s"), *(PlayerTank->GetName()));
    }
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(GetPlayerTank())
    {
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

    if(!PlayerPawn)
    {
        return nullptr;
    }
        
    return Cast<ATank>(PlayerPawn);
}

