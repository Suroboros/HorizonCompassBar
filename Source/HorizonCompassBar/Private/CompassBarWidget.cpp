// Fill out your copyright notice in the Description page of Project Settings.


#include "CompassBarWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"

void UCompassBarWidget::CreateCompassMarker()
{
	if (CompassBarRoot)
	{
		// Get all actor which should be shown on compass bar
		TArray<AActor*> MarkableActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Markable"), MarkableActors);

		// Create marker for each actor
		for (auto actor : MarkableActors)
		{
			UCompassMarker* CompassMarker = NewObject<UCompassMarker>();
			CompassMarker->CreateCompassMarker(WidgetTree, CompassBarRoot, actor);
			CompassMarkers.Add(CompassMarker);
		}
	}
}

void UCompassBarWidget::CreateCompassMarkerWidget()
{
	if (CompassBarRoot)
	{
		// Get all actor which should be shown on compass bar
		TArray<AActor*> MarkableActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Markable"), MarkableActors);

		// Create marker for each actor
		for (auto actor : MarkableActors)
		{
			// Should set unique name for all maker object, otherwise, the all maker will be the same obejct
			UCompassMarkerWidget* CompassMarker = WidgetTree->ConstructWidget<UCompassMarkerWidget>(CompassMarkerWidgetClass, FName("CompassMarker" + actor->GetUniqueID()));
			UCanvasPanelSlot* CompassMarkerSlot = CompassBarRoot->AddChildToCanvas(CompassMarker);
			CompassMarker->Setup(CompassMarkerSlot, actor);
			CompassMarker->SetMarkerColor(FLinearColor::MakeRandomColor());
			CompassMarkerWidgets.Add(CompassMarker);
		}
	}
}

void UCompassBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CompassBarImg)
	{
		// Get compass bar meter material
		CompassBarMaterial = CompassBarImg->GetDynamicMaterial();
		check(CompassBarMaterial);
		UE_LOG(LogTemp, Display, TEXT("%s"), *(CompassBarMaterial->GetFullName()));
	}
}

void UCompassBarWidget::NativeDestruct()
{
	if (CompassBarMaterial)
	{
		CompassBarMaterial = nullptr;
	}

	Super::NativeDestruct();
}

void UCompassBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Scroll compass bar meter
	float compassBarScrollOffset = GetOwningPlayer()->GetControlRotation().Yaw / 360.f;
	CompassBarMaterial->SetScalarParameterValue(TEXT("U_Scroll_Offset"), compassBarScrollOffset);

	// Relocate marker
	for (auto Marker : CompassMarkers)
	{
		Marker->UpdateCompassMarkerPosition(GetOwningPlayer()->GetPawn()->GetActorLocation(), GetOwningPlayer()->GetControlRotation(), Cast<UCanvasPanelSlot>(CompassBarRoot->Slot)->GetSize().X);
	}

	// Relocate marker widget
	for (auto MarkerWidget : CompassMarkerWidgets)
	{
		MarkerWidget->UpdateCompassMarkerPosition(GetOwningPlayer()->GetPawn()->GetActorLocation(), GetOwningPlayer()->GetControlRotation(), Cast<UCanvasPanelSlot>(CompassBarRoot->Slot)->GetSize().X);
	}
}
