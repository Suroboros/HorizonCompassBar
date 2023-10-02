// Fill out your copyright notice in the Description page of Project Settings.


#include "CompassMarkerWidget.h"
#include "Kismet/KismetMathLibrary.h"

void UCompassMarkerWidget::Setup(const TObjectPtr<UCanvasPanelSlot> CanvasPanelSlot, AActor* MarkerOwner)
{
	CompassMarkerWidgetSlot = CanvasPanelSlot;
	CompassMarkerWidgetSlot->SetAnchors(FAnchors(0.5, 0, 0.5, 0));
	CompassMarkerWidgetSlot->SetPosition(FVector2D(0.f, -60.f));
	CompassMarkerWidgetSlot->SetAlignment(FVector2D(0.5f, 0));
	Owner = MarkerOwner;
}

void UCompassMarkerWidget::SetMarkerColor(FLinearColor Color)
{
	CompassMarkerImg->GetDynamicMaterial()->SetVectorParameterValue(TEXT("Color"), Color);
}

void UCompassMarkerWidget::SetOpacity(float Opacity)
{
	CompassMarkerImg->GetDynamicMaterial()->SetScalarParameterValue(TEXT("U_Scroll_Offset"), Opacity);
	DistanceText->GetDynamicFontMaterial()->SetScalarParameterValue(TEXT("U_Scroll_Offset"), Opacity);
}

void UCompassMarkerWidget::UpdateCompassMarkerPosition(const FVector PlayerPostion, const FRotator PlayerControllerRatotor, const float RootSizeX)
{
	check(Owner);

	FVector OwnerPosition = Owner->GetActorLocation();
	FRotator MakerRotator = UKismetMathLibrary::FindLookAtRotation(PlayerPostion, OwnerPosition) - PlayerControllerRatotor;

	// Calculate the distance between the marked actor and player and show it
	int distance = round(FVector::Distance(OwnerPosition, PlayerPostion) / 100.0);
	//DistanceText->SetText(FText::Format(NSLOCTEXT("CompassBar", "DistanceText", "{0}m"), distance));
	DistanceText->SetText(FText::FromString(FString::Printf(TEXT("%dm"), distance)));

	// Relocate marker and text block when player moving or camera rotating
	float MakerPosionXRatio = MakerRotator.Yaw / 360.f;
	SetOpacity(MakerPosionXRatio);
	if (MakerPosionXRatio < -0.5f)
	{
		MakerPosionXRatio += 1.f;
	}
	else if (MakerPosionXRatio > 0.5f)
	{
		MakerPosionXRatio -= 1.f;
	}
	float MarkerPositionX = MakerPosionXRatio * RootSizeX;
	CompassMarkerWidgetSlot->SetPosition(FVector2D(MarkerPositionX, CompassMarkerWidgetSlot->GetPosition().Y));
}
