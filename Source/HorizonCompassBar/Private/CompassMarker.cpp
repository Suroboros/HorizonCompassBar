// Fill out your copyright notice in the Description page of Project Settings.


#include "CompassMarker.h"
#include "Kismet/KismetMathLibrary.h"
#include "Framework/Text/TextLayout.h"

void UCompassMarker::CreateCompassMarker(const TObjectPtr<UWidgetTree> WidgetTree, const TObjectPtr<UCanvasPanel> CanvasRoot, AActor* MarkerOwner)
{
	// Create maker icon material
	TObjectPtr<UMaterialInstance> compassMakerMaterial = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/UI/Materials/MI_CompassMaker"));
	check(compassMakerMaterial);
	CompassMarkerMaterialInst = UMaterialInstanceDynamic::Create(compassMakerMaterial, this);
	check(CompassMarkerMaterialInst);
	CompassMarkerMaterialInst->SetVectorParameterValue(TEXT("Color"), FVector4(UKismetMathLibrary::RandomFloatInRange(0, 1), UKismetMathLibrary::RandomFloatInRange(0, 1), UKismetMathLibrary::RandomFloatInRange(0, 1), 1.f));
	//CompassMarkerMaterialInst->SetVectorParameterValue(TEXT("Color"), FVector4(1.f, 0, 0, 1.f));

	// Create maker icon
	CompassMarkerImg = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), FName("CompassMarkerImg" + MarkerOwner->GetUniqueID()));
	CompassMarkerImg->SetBrushFromMaterial(CompassMarkerMaterialInst);
	CompassMarkerSlot = CanvasRoot->AddChildToCanvas(CompassMarkerImg);
	CompassMarkerSlot->SetAnchors(FAnchors(0.5, 0, 0.5, 0));
	CompassMarkerSlot->SetSize(FVector2D(36, 50));
	CompassMarkerSlot->SetPosition(FVector2D(0.f, -20.f));
	CompassMarkerSlot->SetAlignment(FVector2D(0.5f, 0));

	// Create distance text
	DistanceText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), FName("Distance" + MarkerOwner->GetUniqueID()));
	DistanceText->SetJustification(ETextJustify::Center);
	DistanceTextSlot = CanvasRoot->AddChildToCanvas(DistanceText);
	DistanceTextSlot->SetAnchors(FAnchors(0.5, 0, 0.5, 0));
	DistanceTextSlot->SetPosition(FVector2D(0.f, -50.f));
	DistanceTextSlot->SetAlignment(FVector2D(0.5f, 0));
	DistanceTextSlot->SetAutoSize(true);
	
	Owner = MarkerOwner;
}

void UCompassMarker::UpdateCompassMarkerPosition(float x, float a)
{
	// Test
	CompassMarkerSlot->SetPosition(FVector2D(x, CompassMarkerSlot->GetPosition().Y));
	CompassMarkerMaterialInst->SetScalarParameterValue(TEXT("U_Scroll_Offset"), a);
}

void UCompassMarker::UpdateCompassMarkerPosition(const FVector PlayerPostion, const FRotator PlayerControllerRatotor, const float RootSizeX)
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
	CompassMarkerMaterialInst->SetScalarParameterValue(TEXT("U_Scroll_Offset"), MakerPosionXRatio);
	if (MakerPosionXRatio < -0.5f)
	{
		MakerPosionXRatio += 1.f;
	}
	else if (MakerPosionXRatio > 0.5f)
	{
		MakerPosionXRatio -= 1.f;
	}
	float MarkerPositionX = MakerPosionXRatio * RootSizeX;
	CompassMarkerSlot->SetPosition(FVector2D(MarkerPositionX, CompassMarkerSlot->GetPosition().Y));
	DistanceTextSlot->SetPosition(FVector2D(MarkerPositionX, DistanceTextSlot->GetPosition().Y));


}
