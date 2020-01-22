// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
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
    
    UE_LOG(LogTemp, Warning, TEXT("I am in the BeginPlay method"));
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

