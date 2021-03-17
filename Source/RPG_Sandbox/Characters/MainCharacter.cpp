// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup spring arm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 600.f; // Camera follows at this distance
	SpringArmComponent->bUsePawnControlRotation = true; // Rotate arm based on controller

	// Setup camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Rotation based on spring arm, not camera

	// Hardcode capsule component dimensions
	GetCapsuleComponent()->SetCapsuleSize(44.f, 105.f);

	// Prevents character from rotating with camera (i.e. can swing camera around to see front of character)
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate to face direction of movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f); // Rotation rate for characters
	GetCharacterMovement()->JumpZVelocity = 350.f; // Adjusts how much character jumps
	GetCharacterMovement()->AirControl = 0.2f; // How much character can change direction in air

	// Set Enums
	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::Attack()
{
	// Set IsAttacking
	bAttacking = true;

	// Get AnimInstance
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(!AnimInstance) return;

	// Play montage
	if(!CombatMontage) return;
	AnimInstance->Montage_Play(CombatMontage);
	AnimInstance->Montage_JumpToSection(FName("AttackOne"), CombatMontage);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickHandleStaminaAndSprinting(DeltaTime);
	
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::SprintKeyPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::SprintKeyReleased);
	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMainCharacter::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &AMainCharacter::LMBUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnAtRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpAtRate", this, &AMainCharacter::LookUpAtRate);

}

void AMainCharacter::MoveForward(float Value)
{
	// Ensure controller is not null, and value is not 0
	if(Controller == nullptr || Value == 0.f) return;

	// Get forward position from Controller's yaw
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator ForwardRotation(0.f, Rotation.Yaw, 0.f);

	// Convert to direction vector
	const FVector Direction = FRotationMatrix(ForwardRotation).GetUnitAxis(EAxis::X);

	// Apply movement in correct direction
	AddMovementInput(Direction, Value);
		
}

void AMainCharacter::MoveRight(float Value)
{
	// Ensure controller is not null, and value is not 0
	if(Controller == nullptr || Value == 0.f) return;

	// Get forward position from Controller's yaw
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator ForwardRotation(0.f, Rotation.Yaw, 0.f);

	// Convert to direction vector
	const FVector Direction = FRotationMatrix(ForwardRotation).GetUnitAxis(EAxis::Y);

	// Apply movement in correct direction
	AddMovementInput(Direction, Value);
}

void AMainCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LMBDown()
{
	bLMBDown = true;

	// If overlapping an item, interact with it
	// As of now, only a weapon is available, but other may come later
	if(ActiveOverlappingItem)
	{		
		// If weapon, equip it
		AWeapon* Weapon = Cast<AWeapon>(ActiveOverlappingItem);
		if(Weapon) Weapon->Equip(this);
		return;
	}

	// If a weapon is equipped, attack
	if(EquippedWeapon)
	{
		Attack();
	}

}

void AMainCharacter::LMBUp()
{
	bLMBDown = false;
}

void AMainCharacter::DecrementHealth(float Amount)
{
	// Apply damage
	Health -= Amount;

	// Check if character died
	if(Health <= 0.f)
	{
		
		HandleDeath();
	}
}

void AMainCharacter::HandleDeath()
{
	
}

void AMainCharacter::TickHandleStaminaAndSprinting(float DeltaTime)
{
	const float DeltaStamina = StaminaDrainRate * DeltaTime;

	switch (StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal:
		if(bSprintKeyDown)
		{
			Stamina = FMath::Clamp(Stamina - DeltaStamina, 0.f, MaxStamina);
			if(Stamina <= MinStamina) SetStaminaStatus(EStaminaStatus::ESS_BelowMinimum);
			if(Stamina <= 0.f) SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
			SetMovementStatus(EMovementStatus::EMS_Sprinting);
		}
		else // Sprint key up
			{
			Stamina = FMath::Clamp(Stamina + DeltaStamina, 0.f, MaxStamina);
			SetMovementStatus(EMovementStatus::EMS_Normal);
			}
		break;
	case EStaminaStatus::ESS_BelowMinimum:
		if(bSprintKeyDown)
		{
			Stamina = FMath::Clamp(Stamina - DeltaStamina, 0.f, MaxStamina);
			if(Stamina <= 0.f) SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
			SetMovementStatus(EMovementStatus::EMS_Sprinting);
		}
		else // Sprint key up
		{
			Stamina = FMath::Clamp(Stamina + DeltaStamina, 0.f, MaxStamina);
			if(Stamina > MinStamina) SetStaminaStatus(EStaminaStatus::ESS_Normal);
			SetMovementStatus(EMovementStatus::EMS_Normal);
        }
		break;
	case EStaminaStatus::ESS_Exhausted:
		if(bSprintKeyDown)
		{
			Stamina = 0.f;
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		else // Sprint key up
		{
			Stamina = FMath::Clamp(Stamina += DeltaStamina, 0.f, MaxStamina);
			SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
	case EStaminaStatus::ESS_ExhaustedRecovering:
		Stamina = FMath::Clamp(Stamina + DeltaStamina, 0.f, MaxStamina);
		if(Stamina >= MaxStamina) SetStaminaStatus(EStaminaStatus::ESS_Normal);
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;
	default:
		;
	}
}

void AMainCharacter::SetMovementStatus(EMovementStatus Status)
{
	MovementStatus = Status;
	if(MovementStatus == EMovementStatus::EMS_Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void AMainCharacter::SprintKeyPressed()
{
	bSprintKeyDown = true;
	SetMovementStatus(EMovementStatus::EMS_Sprinting);
}

void AMainCharacter::SprintKeyReleased()
{
	bSprintKeyDown = false;
	SetMovementStatus(EMovementStatus::EMS_Normal);
}
