// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class RPG_SANDBOX_API APickup : public AItemBase
{
	GENERATED_BODY()

public:
	APickup();

protected:

public:
	/** Called when something collides with the CollisionVolume */
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	
	/** Called when something ends collision with CollisionVolume */
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
};
