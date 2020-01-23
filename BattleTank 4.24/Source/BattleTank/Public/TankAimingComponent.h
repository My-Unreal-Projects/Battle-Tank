// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Constructor
	UTankAimingComponent(); // Sets default values for this component's properties

	// Default methods
	virtual void BeginPlay() override; // Called when the game starts

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; // Called every frame

	// Custom methods
	void AimAt(FVector HitLocation);

	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

private:
	UStaticMeshComponent* Barrel = nullptr;

		
};
