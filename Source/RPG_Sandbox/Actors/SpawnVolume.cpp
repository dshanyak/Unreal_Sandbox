// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup components //

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetSpawnPoint() const
{
	// Get dimensions of box
	const FVector Extent = SpawningBox->GetScaledBoxExtent();

	// Get origin location of box
	const FVector Origin = SpawningBox->GetComponentLocation();

	// Get and return random point in box
	FVector SpawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);

	return SpawnPoint;
}

void ASpawnVolume::SpawnPawn_Implementation(UClass* ToSpawn, const FVector& Location)
{
	if(!ToSpawn) return;

	// GetWorld
	UWorld* World = GetWorld();
	if(!World) return;

	// Create default ActorSpawnParameters
	const FActorSpawnParameters SpawnParams;

	ACritter* CritterSpawned = World->SpawnActor<ACritter>(ToSpawn, Location, FRotator(0.f), SpawnParams);
}

