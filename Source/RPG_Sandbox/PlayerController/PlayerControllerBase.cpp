// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

#include "Blueprint/UserWidget.h"


void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	// Generate HUD
	if(HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}

	// Add HUD to display
	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);
}
