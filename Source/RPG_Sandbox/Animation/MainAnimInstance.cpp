// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"

#include "GameFramework/PawnMovementComponent.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Set OwnerPawn
	if(OwnerPawn == nullptr)
	{
		OwnerPawn = TryGetPawnOwner();
	}
}

void UMainAnimInstance::UpdateAnimationProperties()
{
	// Check that we have valid OwnerPawn
	if(OwnerPawn == nullptr)
	{
		OwnerPawn = TryGetPawnOwner();
		if(OwnerPawn == nullptr) return;
	}

	// Update MovementSpeed
	// Not worried about Z directions, only lateral movement
	const FVector Speed = OwnerPawn->GetVelocity();
	const FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
	MovementSpeed = LateralSpeed.Size();

	// Update bIsInAir
	bIsFalling = OwnerPawn->GetMovementComponent()->IsFalling();
	
	
	
}
