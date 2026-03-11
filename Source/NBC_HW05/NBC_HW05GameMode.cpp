// Copyright Epic Games, Inc. All Rights Reserved.

#include "NBC_HW05GameMode.h"
#include "NBC_HW05Character.h"
#include "UObject/ConstructorHelpers.h"

ANBC_HW05GameMode::ANBC_HW05GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
