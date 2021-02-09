// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Explosive.generated.h"

/**
 * 
 */
UCLASS()
class RPG_SANDBOX_API AExplosive : public AItemBase
{
	GENERATED_BODY()

public:
	AExplosive();

	/** Damage dealt by explosive */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage = 15.f;

protected:

public:
	/** Called when something collides with the CollisionVolume */
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	
	/** Called when something ends collision with CollisionVolume */
    virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
};
