// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/TSS_GameMode.h"

#include "Enums/CurrentPlayState.h"
#include "UObject/ConstructorHelpers.h"

ATheSailingSirenGameMode::ATheSailingSirenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	this->CurrentPlayState = ECurrentPlayState::RiddleOne;
}
