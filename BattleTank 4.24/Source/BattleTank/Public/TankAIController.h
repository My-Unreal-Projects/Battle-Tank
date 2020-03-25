// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declarations
class UTankAimingComponent;
class APlayerController;
class UWorld;
class ATank;


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	// Default methods
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void SetPawn(APawn* InPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 7000; // How close the AI tank get to the player tank

private:
	UFUNCTION()
	void OnPossessedTankDeath();
};
