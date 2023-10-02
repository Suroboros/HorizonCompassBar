// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "CompassMarkerWidget.generated.h"

/**
 * 
 */
UCLASS()
class HORIZONCOMPASSBAR_API UCompassMarkerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	/// <summary>
	/// Set widget layout and marked actor
	/// </summary>
	void Setup(const TObjectPtr<UCanvasPanelSlot> Slot, AActor* MarkerOwner);

	/// <summary>
	/// Set the color of marker
	/// </summary>
	void SetMarkerColor(FLinearColor Color);

	/// <summary>
	/// Set the Opacity of marker and text when widget relocate
	/// </summary>
	void SetOpacity(float Opacity);

	/// <summary>
	/// Update widget position on compass bar
	/// </summary>
	void UpdateCompassMarkerPosition(const FVector PlayerPostion, const FRotator PlayerControllerRatotor, const float RootSizeX);

private:
	// Marker image
	UPROPERTY(EditAnywhere, Category = HUD, meta = (BindWidget))
		TObjectPtr<UImage> CompassMarkerImg;

	// Distance text block
	UPROPERTY(EditAnywhere, Category = HUD, meta = (BindWidget))
		TObjectPtr<UTextBlock> DistanceText;

	// The marked actor by this marker
	UPROPERTY(EditAnywhere, Category = HUD)
		TObjectPtr<AActor> Owner;

	// Widget canvas panel slot
	UPROPERTY(EditAnywhere, Category = HUD)
		TObjectPtr<UCanvasPanelSlot> CompassMarkerWidgetSlot;
};
