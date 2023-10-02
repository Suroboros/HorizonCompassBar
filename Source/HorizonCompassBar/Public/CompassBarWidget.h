// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "CompassMarker.h"
#include "CompassMarkerWidget.h"
#include "CompassBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class HORIZONCOMPASSBAR_API UCompassBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Compass bar meter image
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UImage> CompassBarImg;

	// Root canvas which marker can be attached to
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		TObjectPtr<UCanvasPanel> CompassBarRoot;

	// Create compass marker(with out marker widget)
	UFUNCTION()
		void CreateCompassMarker();

	// Create compass marker(with marker widget)
	UFUNCTION()
		void CreateCompassMarkerWidget();

protected:
	void NativeConstruct() override;
	void NativeDestruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	
	// Compass bar meter material(for meter scrolling)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UMaterialInstanceDynamic> CompassBarMaterial;

	/*
	* The property with out marker widget creation
	*/
	// Marker array(with out marker widget)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
		TArray<UCompassMarker*> CompassMarkers;

	/*
	* The property with out marker widget creation
	*/
	// Marker array(with marker widget)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
		TArray<UCompassMarkerWidget*> CompassMarkerWidgets;

	// The marker widget class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UCompassMarkerWidget> CompassMarkerWidgetClass;
};
