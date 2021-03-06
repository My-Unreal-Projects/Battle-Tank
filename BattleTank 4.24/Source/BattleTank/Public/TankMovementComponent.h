// Copyright Cesar Molto Morilla

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward declarations
class UTankTrack;

/**
 * Class responsible for driving the tank tracks
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

	UTankTrack* RightTrack = nullptr;
	UTankTrack* LeftTrack = nullptr;

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

private:
	// Called from the pathfinding logic by the AI controllers
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;	
};
