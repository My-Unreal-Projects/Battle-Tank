// Copyright Cesar Molto Morilla

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet)
{
    if(!ensure(LeftTrackToSet && RightTrackToSet)) {return;}

    RightTrack = RightTrackToSet;
    LeftTrack = LeftTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    // No need to call Super() as we're replacing the whole functionality
    FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

    float ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
    IntendMoveForward(ForwardThrow);

    float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
    IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if(!ensure(LeftTrack && RightTrack)) {return;}

    RightTrack->SetThrottle(Throw);
    LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if(!ensure(LeftTrack && RightTrack)) {return;}

    RightTrack->SetThrottle(-Throw);
    LeftTrack->SetThrottle(Throw);
}