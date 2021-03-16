// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ItemBase.h"

#include "Weapon.generated.h"

class AMainCharacter;
/**
 * 
 */
UCLASS()
class RPG_SANDBOX_API AWeapon : public AItemBase
{
	GENERATED_BODY()

protected:
	/** MeshComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
	USkeletalMeshComponent* SkeletalMesh;

	/** Sound to play when equipping the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Effects")
	USoundCue* OnEquippedSound;

	/** Determines if weapon should continue running particles after equipping */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Effects")
	bool bPlayParticlesAfterEquip = false;

public:
	AWeapon();

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	/** Called to equip weapon */
	UFUNCTION(BlueprintCallable)
	void Equip(AMainCharacter* Character);
};
