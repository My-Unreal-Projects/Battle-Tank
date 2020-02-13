// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

// Called once at the beginning of the game
void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    ControlledTank = Cast<ATank>(GetPawn());

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

    if(PlayerTank)
    {
        // Aim towards the player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        // Fire if ready
        ControlledTank->Fire(); // TODO limit firing rate
    }
}
