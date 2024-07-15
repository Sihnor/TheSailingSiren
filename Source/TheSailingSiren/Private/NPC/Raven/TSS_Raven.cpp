// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Raven/TSS_Raven.h"

#include "Enums/CurrentPlayState.h"
#include "GameMode/TSS_GameMode.h"


// Sets default values
ARaven::ARaven()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(this->Root);

	this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	this->MeshComponent->SetupAttachment(this->Root);

	this->MeshComponent->OnClicked.AddUniqueDynamic(this, &ARaven::OnRavenClicked);
}

// Called when the game starts or when spawned
void ARaven::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARaven::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARaven::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARaven::OnRavenClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Raven Clicked"));

	// Get Current GameMode
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();

	if(const ATheSailingSirenGameMode* TssGameMode = Cast<ATheSailingSirenGameMode>(GameMode))
	{
		switch (const ECurrentPlayState CurrentPlayState = TssGameMode->GetCurrentPlayState())
		{
		case ECurrentPlayState::RiddleOne:
			PlayHintForRiddleOne();
			break;
		case ECurrentPlayState::RiddleTwo:
			PlayHintForRiddleTwo();
			break;
		case ECurrentPlayState::RiddleThree:
			PlayHintForRiddleThree();
			break;
		case ECurrentPlayState::RiddleFour:
			PlayHintForRiddleFour();
			break;
		case ECurrentPlayState::RiddleFive:
			PlayHintForRiddleFive();
			break;
			default: ;
		}
	}
}

void ARaven::PlayHintForRiddleOne()
{
	
}

void ARaven::PlayHintForRiddleTwo()
{
}

void ARaven::PlayHintForRiddleThree()
{
}

void ARaven::PlayHintForRiddleFour()
{
}

void ARaven::PlayHintForRiddleFive()
{
}


