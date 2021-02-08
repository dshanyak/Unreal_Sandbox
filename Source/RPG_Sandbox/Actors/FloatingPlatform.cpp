// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	StartPoint = FVector(0.f);
	EndPoint = FVector(0.f);

}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Set StartPoint
	StartPoint = GetActorLocation();
	
	/**
	 *SetEndpoint
	 *EndPoint by default is a relative position vector
	 *By adding the relative vector to StartPoint, you get the worl location
	 **/
	EndPoint += StartPoint;

	// Setup InterpHandle
	GetWorldTimerManager().SetTimer(InterpHandle, this, &AFloatingPlatform::ToggleInterping, InterpTime);

	// Set Distance
	Distance = (EndPoint - StartPoint).Size();

}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsInterping)
	{
		// Move platform towards endpoint
		const FVector Interp = FMath::VInterpTo(GetActorLocation(), EndPoint, DeltaTime, PlatformSpeed);
		SetActorLocation(Interp);

		float DistanceTraveled = (GetActorLocation() - StartPoint).Size();
		if(Distance - DistanceTraveled < 1.f)
		{
			ToggleInterping();

			GetWorldTimerManager().SetTimer(InterpHandle, this, &AFloatingPlatform::ToggleInterping, InterpTime);
			SwapVectors(StartPoint, EndPoint);
		}
	}
	
}

void AFloatingPlatform::ToggleInterping()
{
	bIsInterping = !bIsInterping;
}

void AFloatingPlatform::SwapVectors(FVector& VecOne, FVector& VecTwo)
{
	const FVector Temp = VecOne;
	VecOne = VecTwo;
	VecTwo = Temp;
}

