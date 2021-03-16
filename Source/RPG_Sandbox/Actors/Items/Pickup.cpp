// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "RPG_Sandbox/Characters/MainCharacter.h"

APickup::APickup()
{
	
}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	// Cast other actor to
	AMainCharacter* Player = nullptr;
	if(OtherActor)
	{
		Player = Cast<AMainCharacter>(OtherActor);
	}
	if(!Player) return;

	// Add coins to player's inventory
	Player->Coins += 1;

	Destroy();
	
}

void APickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	
}
