// Copyright Epic Games, Inc. All Rights Reserved.

#include "GasExSampleGameMode.h"
#include "GasExSampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGasExSampleGameMode::AGasExSampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_BasePlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
