// Copyright Cesar Molto Morilla


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	float DeltaTime = GetWorld()->DeltaTimeSeconds;

	// Move the turret the right amount this frame
	// Given a max elevation speed and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * DeltaTime;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}