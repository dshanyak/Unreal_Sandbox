// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"

#include "ItemBase.generated.h"

UCLASS()
class RPG_SANDBOX_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	/** Base shape collision */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Collision")
	USphereComponent* CollisionVolume;

	/** Base mesh component  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Mesh")
	UStaticMeshComponent* Mesh;

	/** Idle particle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles")
	UParticleSystemComponent* IdleParticle;

	/** Overlap particle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles")
	UParticleSystem* OverlapParticle;

	/** Plays when player overlaps item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sounds")
	USoundCue* OverlapSound;

	/** Determines if item should rotate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Properties")
	bool bRotate = false;

	/** How quickly item should rotate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Properties")
	float RotationSpeed = 45.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Called when something collides with the CollisionVolume */
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
	/** Called when something ends collision with CollisionVolume */
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {}

};

