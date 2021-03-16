// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "RPG_Sandbox/Characters/MainCharacter.h"

AWeapon::AWeapon()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());
}


void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	// Set character's overlapping item to this
	if(!OtherActor) return;
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if(!MainCharacter) return;
	MainCharacter->SetOverlappedItem(this);
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	// Remove character's overlapping item
	if(!OtherActor) return;
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if(!MainCharacter) return;
	MainCharacter->SetOverlappedItem(nullptr);
	
}

void AWeapon::Equip(AMainCharacter* Character)
{
	// Check parameters
	if(!Character || !SkeletalMesh) return;

	// Keeps camera from glitching if sword gets between character and camera
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	// Disable collision with pawn
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	// Stop simulating physics
	SkeletalMesh->SetSimulatePhysics(false);

	// Get Socket to attach to
	const USkeletalMeshSocket* RightHandSocket = Character->GetMesh()->GetSocketByName("RightHandSocket");
	if(!RightHandSocket) return;

	// Attach weapon
	RightHandSocket->AttachActor(this, Character->GetMesh());
	Character->SetEquippedWeapon(this);

	// Stop rotating weapon
	bRotate = false;

	// Play equipped sound
	if(OnEquippedSound)
		UGameplayStatics::PlaySound2D(GetWorld(), OnEquippedSound);

	if(!bPlayParticlesAfterEquip)
		IdleParticle->Deactivate();
	
}
