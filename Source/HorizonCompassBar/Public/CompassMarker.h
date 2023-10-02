// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CompassMarker.generated.h"

/**
 * 
 */
UCLASS()
class HORIZONCOMPASSBAR_API UCompassMarker : public UObject
{
	GENERATED_BODY()

public:
	/// <summary>
	/// Create compass marker image and distance text
	/// </summary>
	void CreateCompassMarker(const TObjectPtr<UWidgetTree> WidgetTree, const TObjectPtr<UCanvasPanel> CanvasRoot, AActor* MarkerOwner);

	/// <summary>
	/// Update compass marker`s position(for testing)
	/// </summary>
	void UpdateCompassMarkerPosition(float x, float a);

	/// <summary>
	/// Update compass marker`s position on compass bar and change opacity according position
	/// </summary>
	void UpdateCompassMarkerPosition(const FVector PlayerPostion, const FRotator PlayerControllerRatotor, const float RootSizeX);

private:
	// Compass marker image material
	UPROPERTY()
		TObjectPtr<UMaterialInstanceDynamic> CompassMarkerMaterialInst;

	// Compass marker image
	UPROPERTY()
		TObjectPtr<UImage> CompassMarkerImg;

	// Compass marker image canvas panel slot
	UPROPERTY()
		TObjectPtr<UCanvasPanelSlot> CompassMarkerSlot;

	// Distance text block
	UPROPERTY()
		TObjectPtr<UTextBlock> DistanceText;

	// Distance text block canvas panel slot
	UPROPERTY()
		TObjectPtr<UCanvasPanelSlot> DistanceTextSlot;
	
	// The marked actor by this marker
	UPROPERTY()
		TObjectPtr<AActor> Owner;
};
