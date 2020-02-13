// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declarations
class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private: 
	// Default methods
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	// Custom methods

	// Custom variables
	ATank* PlayerTank = nullptr;
	ATank* ControlledTank = nullptr;
};
