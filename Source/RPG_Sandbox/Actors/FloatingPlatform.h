// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

UCLASS()
class RPG_SANDBOX_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingPlatform();

	/** Mesh for the platform */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform")
	UStaticMeshComponent* Mesh;

	/** Starting location of platform */
	UPROPERTY(EditAnywhere)
	FVector StartPoint;

	/** Starting location of endpoint (where platform will move to) */
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"))
	FVector EndPoint;

	/** How quickly the platform moves */
	UPROPERTY(EditAnywhere, Category = "Platform")
	float PlatformSpeed = 10.f;

	/** Timer for platform movement */
	UPROPERTY(EditAnywhere, Category = "Platform")
	float InterpTime = 1.f;

	/** Whether or not the platform in interping */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform")
	bool bIsInterping = false;

	/** How close platform is to goal location */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform")
	float Distance = 0.f;

	/** Timer handle for moving the platform */
	FTimerHandle InterpHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to toggle bIsInterping
	void ToggleInterping();

	// Used to swap direction of platform
	void SwapVectors(FVector& VecOne, FVector& VecTwo);
	

};
