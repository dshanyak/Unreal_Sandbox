// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "RPG_Sandbox/Pawns/Critter.h"

#include "SpawnVolume.generated.h"

UCLASS()
class RPG_SANDBOX_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<ACritter> PawnToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns a random point from within the box */
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetSpawnPoint() const;

	/** */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spawning")
	void SpawnPawn(UClass* ToSpawn, const FVector& Location);
	

};
