// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheSailingSirenGameMode.h"
#include "TheSailingSiren/Public/Character/TSS_Character.h"
#include "UObject/ConstructorHelpers.h"

ATheSailingSirenGameMode::ATheSailingSirenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
