// Copyright Cesar Molto Morilla

#include "TankAIController.h"
#include "TankAimingComponent.h"

// Called once at the beginning of the game
void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();

    if(!ensure(PlayerTank)) {return;}
    // Move towards player
    MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check if radius is in cm

    if(!ensure(ControlledTank)) {return;}

    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>(); 
    if(!ensure(AimingComponent)) {return;}

    // Aim towards the player
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    // Fire if ready
    if(AimingComponent->GetFiringState() == EFiringState::Locked)
        AimingComponent->Fire();
}
