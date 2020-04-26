// Copyright Cesar Molto Morilla

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

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

    if(!PlayerTank) {return;}
    // Move towards player

    MoveToActor(PlayerTank, AcceptanceRadius);

    if(!ControlledTank) {return;}

    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>(); 
    if(!AimingComponent) {return;}

    // Aim towards the player
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    FHitResult HitResult;

    auto StartLocation = ControlledTank->GetActorLocation() + FVector(0, 0, 150);
    auto EndLocation = PlayerTank->GetActorLocation() + FVector(0, 0, 150);

    if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Pawn))
    {
        // UE_LOG(LogTemp, Warning, TEXT("%s hit result actor: %s"), *this->GetPawn()->GetName(), *HitResult.Actor->GetName());
        // Fire if ready
        if(AimingComponent->GetFiringState() != EFiringState::Reloading && AimingComponent->GetFiringState() != EFiringState::OutOfAmmo && HitResult.Actor == PlayerTank)
            AimingComponent->Fire();
    }
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if(!InPawn) {return;}
    auto PossessedTank = Cast<ATank>(InPawn);

    if(!PossessedTank) {return;}

    PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
}

void ATankAIController::OnPossessedTankDeath()
{
    if(!GetPawn()) {return;}

    PossessedTankDead();
    GetPawn()->DetachFromControllerPendingDestroy();
}
