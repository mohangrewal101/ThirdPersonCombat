// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonCombatGameMode.h"
#include "ThirdPersonCombatCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThirdPersonCombatGameMode::AThirdPersonCombatGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
