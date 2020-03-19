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

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 7000; // How close the AI tank get to the player tank

private: 
	// Default methods
	void BeginPlay() override;

	void Tick(float DeltaTime) override;
};
