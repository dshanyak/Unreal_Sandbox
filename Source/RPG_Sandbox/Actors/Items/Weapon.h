// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ItemBase.h"
#include "RPG_Sandbox/Characters/MainCharacter.h"

#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class RPG_SANDBOX_API AWeapon : public AItemBase
{
	GENERATED_BODY()

public:
	AWeapon();

	/** MeshComponent */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
	USkeletalMeshComponent* SkeletalMesh;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	/** Called to equip weapon */
	UFUNCTION(BlueprintCallable)
	void Equip(AMainCharacter* Character);
};
