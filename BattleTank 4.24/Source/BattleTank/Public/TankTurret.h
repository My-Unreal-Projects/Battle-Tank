// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * Class responsible for moving the barrel towards the aiming direction
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 25;

public:
	// -1 is max downward speed, and +1 is max up movement
	void Rotate(float RelativeSpeed);
};
