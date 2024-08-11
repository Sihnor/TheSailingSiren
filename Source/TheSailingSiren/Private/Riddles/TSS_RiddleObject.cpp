// Fill out your copyright notice in the Description page of Project Settings.


#include "Riddles/TSS_RiddleObject.h"

#include "GameMode/TSS_GameMode.h"


// Sets default values
ARiddleObject::ARiddleObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = this->Root;

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->Mesh->SetupAttachment(this->Root);

	this->CameraPosition = CreateDefaultSubobject<USceneComponent>(TEXT("CameraPosition"));
	this->CameraPosition->SetupAttachment(this->Root);

	
	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
}

void ARiddleObject::BeginPlay()
{
	Super::BeginPlay();

	if (!this->Letter) return;
	this->Letter->SetActorHiddenInGame(true);
	this->Letter->SetActorEnableCollision(false);
	this->Letter->SetActorTickEnabled(false);
}

const USceneComponent*  ARiddleObject::Interact_Implementation()
{
	// Get GameMode
	const ATheSailingSirenGameMode* GameMode = Cast<ATheSailingSirenGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr) return nullptr;
	if (GameMode->GetCurrentPlayState() != this->RiddleState)
	{
		return nullptr;
	}

	StartRiddle();
	return this->CameraPosition;
}

