// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// UE_LOG(LogTemp, Warning, TEXT("Inside Turret->Rotate function"));

	float DeltaTime = GetWorld()->DeltaTimeSeconds;

	// Move the turret the right amount this frame
	// Given a max elevation speed and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * DeltaTime;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	// UE_LOG(LogTemp, Warning, TEXT("NewRotation: %f"), NewRotation);

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}