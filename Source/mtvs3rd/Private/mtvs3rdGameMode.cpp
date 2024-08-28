// Copyright Epic Games, Inc. All Rights Reserved.

#include "mtvs3rdGameMode.h"
#include "mtvs3rdCharacter.h"
#include "UObject/ConstructorHelpers.h"

Amtvs3rdGameMode::Amtvs3rdGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
