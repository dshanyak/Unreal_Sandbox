// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RPG_Sandbox/Characters/MainCharacter.h"

#include "MainAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPG_SANDBOX_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// Similar to BeginPlay
	virtual void NativeInitializeAnimation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	APawn* OwnerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	AMainCharacter* MainCharacter;

private:
	//** Called every frame to update variables */
	UFUNCTION(BlueprintCallable, Category = "AnimationProperties")
	void UpdateAnimationProperties();

	
	
};
