// Copyright Cesar Molto Morilla


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
    auto Name = GetName(); 
    // UE_LOG(LogTemp, Warning, TEXT("%s value is: %f"), *Name, Throttle);

    // TODO Clamp actual throttle value so player can not over-drive
    FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    FVector ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

