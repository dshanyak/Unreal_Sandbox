// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "RPG_Sandbox/Actors/Items/Weapon.h"


#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal		UMETA(DisplayName = "Normal"),
	EMS_Sprinting	UMETA(DisplayName = "Sprinting"),

	EMS_MAX			UMETA(DisplayName = "DefaultMax")
	
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal				UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum		UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted			UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering	UMETA(DisplayName = "ExhaustedRecovering"),

	ESS_MAX					UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class RPG_SANDBOX_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	/** Weapon wielded by character */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	AWeapon* EquippedWeapon;

	/** Setup equipped weapon */
	UFUNCTION(BlueprintCallable)
	void SetEquippedWeapon(AWeapon* WeaponToSet) { EquippedWeapon = WeaponToSet; }

	/** Stamina */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;

	/** Rate at which stamina depleats */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float StaminaDrainRate = 25.f;

	/** Minimum stamina before being exhausted */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MinStamina = 50.f;

	/** Set StaminaStatus */
	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) {StaminaStatus = Status;}

	/** Called in Tick to update/check sprinting/stamina status */
	UFUNCTION()
	void TickHandleStaminaAndSprinting(float DeltaTime);

	/** Movement */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed = 650.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SprintingSpeed = 950.f;

	/** Set movement and running speed */
	void SetMovementStatus(EMovementStatus Status);

	/** Is srpint key pressed */
	bool bSprintKeyDown = false;

	/** Called when sprint key is pressed */
	void SprintKeyPressed();

	/** Called when sprint key not pressed */
	void SprintKeyReleased();

	/** Spring arm components */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	/** Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	/** Base turn rate to scale turning functions for the camera */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate = 65.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate = 65.f;

	/**
	 *
	 * Player Stats
	 *
	 *
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health = 65.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxStamina = 350.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina = 120.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Coins = 0;

	void DecrementHealth(float Amount);
	void HandleDeath();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forward/backwards input */
	void MoveForward(float Value);

	/** Called for side/side input */
	void MoveRight(float Value);

	/** Called via input to turn at a given rate
	 * @Param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/** Called via input to look up/down at a given rate
	* @Param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	// Getters for components
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const {return SpringArmComponent;}
	FORCEINLINE UCameraComponent* GetCameraComponent() const {return CameraComponent;}
};
