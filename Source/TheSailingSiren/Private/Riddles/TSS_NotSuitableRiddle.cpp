﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Riddles/TSS_NotSuitableRiddle.h"
#include "Objects/TSS_NotSuitablePiece.h"

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

	StartRiddle();
	
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

void ANotSuitableRiddle::StartRiddle()
{
	if(!CheckForAnotherRound()) return;
	
	int WrongIndex = FMath::RandRange(0, 4);

	while (this->RightPlaces & (1 << WrongIndex))
	{
		WrongIndex = FMath::RandRange(0, 4);
	}
	
	for (size_t i = 0; i < 5; i++)
	{
		if(this->RightPlaces & (1 << i))continue;
		
		ANotSuitablePiece* NewPiece = GetWorld()->SpawnActor<ANotSuitablePiece>(this->Piece);
		NewPiece->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		FVector NewLocation = FVector(0.0f, -20.0f, 0.0f);
		NewLocation.Y += i * 10.0f;

		NewLocation += this->GetActorLocation();

		NewPiece->SetActorLocation(NewLocation);

		if(WrongIndex == i)
		{
			NewPiece->PieceMesh->SetMaterial(0, this->NotSuitableMaterials[FMath::RandRange(0, this->NotSuitableMaterials.Num() - 1)]);
			NewPiece->SetRightPiece(false);
			
			this->CurrentWrongPiece = NewPiece;
			this->CurrentWrongPiece->OnWrongPieceFound.AddDynamic(this, &ANotSuitableRiddle::StartNextRound);

			this->RightPlaces |= 1 << WrongIndex;
		}
		else
		{
			int MaterialIndex = FMath::RandRange(0, this->SuitableMaterials.Num() - 1);
			NewPiece->PieceMesh->SetMaterial(0, this->SuitableMaterials[MaterialIndex]);
			this->AllRightPieces.Add(NewPiece);
		}

	}
}

void ANotSuitableRiddle::StartNextRound()
{
	this->CurrentWrongPiece->OnWrongPieceFound.RemoveDynamic(this, &ANotSuitableRiddle::StartNextRound);
	
	for (const auto Element : this->AllRightPieces)
	{
		Element->Destroy();
	}

	this->AllRightPieces.Empty();

	StartRiddle();
}

bool ANotSuitableRiddle::CheckForAnotherRound()
{
	for (size_t i = 0; i < 5; i++)
	{
		if(!(this->RightPlaces & (1 << i)))
		{
			return true;
		}
	}

	return false;
}


