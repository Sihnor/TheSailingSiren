// Fill out your copyright notice in the Description page of Project Settings.


#include "Riddles/TSS_NotSuitableRiddle.h"


// Sets default values
ANotSuitableRiddle::ANotSuitableRiddle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANotSuitableRiddle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANotSuitableRiddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const USceneComponent* ANotSuitableRiddle::Interact_Implementation()
{
	return this->CameraPosition;
}

