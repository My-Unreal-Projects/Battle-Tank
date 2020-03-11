// Copyright Cesar Molto Morilla


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// UE_LOG(LogTemp, Warning, TEXT("Inside Barrel->Elevate function"));

	float DeltaTime = GetWorld()->DeltaTimeSeconds;

	// Move the barrel the right amount this frame
	// Given a max elevation speed and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * DeltaTime;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}