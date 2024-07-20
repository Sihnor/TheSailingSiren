// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TSS_NotSuitablePiece.h"


// Sets default values
ANotSuitablePiece::ANotSuitablePiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ANotSuitablePiece::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (!this->bIsRightPiece)
	{
		
	}
}

void ANotSuitablePiece::OnRelease(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
}

// Called when the game starts or when spawned
void ANotSuitablePiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANotSuitablePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

