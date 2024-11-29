// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheCubeGameMode.h"
#include "TheCubeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheCubeGameMode::ATheCubeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
