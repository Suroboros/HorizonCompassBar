// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorizonCompassBarGameMode.h"
#include "HorizonCompassBarCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHorizonCompassBarGameMode::AHorizonCompassBarGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Blueprints/BP_MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
