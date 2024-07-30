// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/TSS_GameMode.h"

#include "Enums/CurrentPlayState.h"
#include "Riddles/TSS_RiddleObject.h"
#include "UObject/ConstructorHelpers.h"

void ATheSailingSirenGameMode::BeginPlay()
{
	Super::BeginPlay();
return;

		for (int i = 0; i < this->AllRiddles.Num(); i++)
		{
			this->AllRiddles[i]->OnRiddleSolved.AddUniqueDynamic(this, &ATheSailingSirenGameMode::OnRiddleSolved);
			this->AllRiddles[i]->SetRiddleIndex(static_cast<ECurrentPlayState>(i + 1));
		}
}

ATheSailingSirenGameMode::ATheSailingSirenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	this->CurrentPlayState = ECurrentPlayState::RiddleOne;
}

void ATheSailingSirenGameMode::OnRiddleSolved(const int CurrentRiddleIndex)
{
	if(this->CurrenRiddle == CurrentRiddleIndex)
	{
		this->CurrenRiddle++;
		this->CurrentPlayState = static_cast<ECurrentPlayState>(this->CurrenRiddle);
	}
}
