// Copyright Cesar Molto Morilla

#pragma once

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declarations
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private: 
	// Default methods
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	float AcceptanceRadius = 3000; // How close the AI tank get to the player tank
};
