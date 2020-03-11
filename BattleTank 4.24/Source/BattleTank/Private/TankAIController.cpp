// Copyright Cesar Molto Morilla

#include "TankAIController.h"
#include "Tank.h"

// Called once at the beginning of the game
void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    ControlledTank = Cast<ATank>(GetPawn());
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!ensure(PlayerTank && ControlledTank)) {return;}

    // Move towards player
    MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check if radius is in cm

    // Aim towards the player
    ControlledTank->SetHitLocation(PlayerTank->GetActorLocation());

    // Fire if ready
    ControlledTank->Fire(); // TODO limit firing rate
}
