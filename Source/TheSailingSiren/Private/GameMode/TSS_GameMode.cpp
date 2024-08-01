// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/TSS_GameMode.h"

#include "Enums/CurrentPlayState.h"
#include "Riddles/TSS_RiddleObject.h"
#include "UObject/ConstructorHelpers.h"

void ATheSailingSirenGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < this->AllRiddles.Num(); i++)
	{
		if (this->AllRiddles[i] == nullptr) continue;
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

void ATheSailingSirenGameMode::OnRiddleSolved(const ECurrentPlayState CurrentRiddleIndex)
{
	// print CurrentRiddleIndex
	UE_LOG(LogTemp, Warning, TEXT("Current Riddle Index: %d"), static_cast<int>(CurrentRiddleIndex));
	// print this->CurrentPlayState
	UE_LOG(LogTemp, Warning, TEXT("Current Play State: %d"), static_cast<int>(this->CurrentPlayState));
	
	if(this->CurrentPlayState == CurrentRiddleIndex)
	{
		int CurrentGameIndex = static_cast<int>(this->CurrentPlayState);
		CurrentGameIndex++;
		this->CurrentPlayState = static_cast<ECurrentPlayState>(CurrentGameIndex);
	}
}
