// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosive.h"

#include "RPG_Sandbox/Characters/MainCharacter.h"

AExplosive::AExplosive()
{
	
}

void AExplosive::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

	// Apply damage to player
	Player->DecrementHealth(Damage);

	Destroy();
	
}

void AExplosive::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	
}


