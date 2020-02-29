// Copyright Cesar Molto Morilla

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
        // Move towards player
        MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check if radius is in cm

        // Aim towards the player
        ControlledTank->SetHitLocation(PlayerTank->GetActorLocation());

        // Fire if ready
        ControlledTank->Fire(); // TODO limit firing rate
    }
}
