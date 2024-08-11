// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/TSS_GameMode.h"

#include "Enums/CurrentPlayState.h"
#include "Riddles/TSS_RiddleObject.h"
#include "UObject/ConstructorHelpers.h"


void ATheSailingSirenGameMode::OnStartIntroduction_Implementation()
{
}

void ATheSailingSirenGameMode::OnEndIntroduction_Implementation()
{
}

void ATheSailingSirenGameMode::DelayMotSound()
{
	// Delay after 3 seconds
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATheSailingSirenGameMode::OnMotNoise, 5.0f, false);
}

void ATheSailingSirenGameMode::OnMotNoise_Implementation()
{
}

void ATheSailingSirenGameMode::OnStartFirstDialogueMotAndSamael_Implementation()
{
}

void ATheSailingSirenGameMode::OnStartFindTranslation_Implementation()
{
}

void ATheSailingSirenGameMode::OnStartRiddleTwo_Implementation()
{
}

void ATheSailingSirenGameMode::OnStartSecondDialogMotAndSamael_Implementation()
{
}

void ATheSailingSirenGameMode::PlayDoorSound()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATheSailingSirenGameMode::OnStartRiddleThreeAndFour, 1.0f, false);
}

void ATheSailingSirenGameMode::OnStartRiddleThreeAndFour_Implementation()
{
}

void ATheSailingSirenGameMode::OnOpenTrapdoor_Implementation()
{
}

void ATheSailingSirenGameMode::OnLastLetterCollected()
{
	OnCollectLetter();
}

void ATheSailingSirenGameMode::OnCollectLetter_Implementation()
{
}

void ATheSailingSirenGameMode::PlayReadLetterSound()
{
	OnReadLetter();
}

void ATheSailingSirenGameMode::OnReadLetter_Implementation()
{
}

void ATheSailingSirenGameMode::StartLastDialogue()
{
	OnLastDialogueMotAndSamael();
}

void ATheSailingSirenGameMode::OnLastDialogueMotAndSamael_Implementation()
{
}

void ATheSailingSirenGameMode::OnMonologueMot_Implementation()
{
}

void ATheSailingSirenGameMode::OnMonologueSamael_Implementation()
{
}

void ATheSailingSirenGameMode::StartFirstDialogue()
{
	OnRiddleSolved(ECurrentPlayState::None);
}

void ATheSailingSirenGameMode::StartSecondDialogue()
{
	OnStartSecondDialogueMotAndSamael();
}


void ATheSailingSirenGameMode::OnStartRiddleOne_Implementation()
{
}


void ATheSailingSirenGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < this->AllRiddles.Num(); i++)
	{
		if (this->AllRiddles[i] == nullptr) continue;
		this->AllRiddles[i]->OnRiddleSolved.AddUniqueDynamic(this, &ATheSailingSirenGameMode::OnRiddleSolved);
		this->AllRiddles[i]->SetRiddleIndex(static_cast<ECurrentPlayState>(i + 1));
	}

	this->OnStartIntroduction();
	//OnRiddleSolved(ECurrentPlayState::None);
}

ATheSailingSirenGameMode::ATheSailingSirenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	this->CurrentPlayState = ECurrentPlayState::None;
}

void ATheSailingSirenGameMode::OnRiddleSolved_Implementation(ECurrentPlayState CurrentRiddleIndex)
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

	switch (CurrentRiddleIndex) {
	case ECurrentPlayState::None:
		OnStartFirstDialogueMotAndSamael();
		break;
	case ECurrentPlayState::RiddleOne:
	case ECurrentPlayState::RiddleTwo:
	case ECurrentPlayState::RiddleThree:
		PlayRiddleSolvedSound();
		break;
	case ECurrentPlayState::RiddleFour:
		this->OnOpenTrapdoor();
		break;
	case ECurrentPlayState::RiddleFive:
		break;
	case ECurrentPlayState::Finished:
		break;
	}
}

void ATheSailingSirenGameMode::StartSamaelMonologue()
{
	OnMonologueSamael();
}

void ATheSailingSirenGameMode::StartMotMonologue()
{
	OnMonologueMot();
}
