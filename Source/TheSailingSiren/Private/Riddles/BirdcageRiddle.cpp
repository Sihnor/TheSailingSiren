// Fill out your copyright notice in the Description page of Project Settings.


#include "Riddles/BirdcageRiddle.h"


// Sets default values
ABirdcageRiddle::ABirdcageRiddle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->BirdcageDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BirdcageDoor"));
	this->BirdcageDoor->SetupAttachment(this->Root);
}

void ABirdcageRiddle::BroadCastRiddleFinished()
{
	this->OnRiddleSolved.Broadcast(GetRiddleIndex());
}

// Called when the game starts or when spawned
void ABirdcageRiddle::BeginPlay()
{
	Super::BeginPlay();
}

const USceneComponent* ABirdcageRiddle::Interact_Implementation()
{
	const USceneComponent* ReturnValue = Super::Interact_Implementation();

	if (ReturnValue != nullptr)
	{
		ShowInvertory();
	}

	return ReturnValue;
}

// Called every frame
void ABirdcageRiddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABirdcageRiddle::StopRiddle()
{
	Super::StopRiddle();

	HideInventory();
}

