// Fill out your copyright notice in the Description page of Project Settings.


#include "Riddles/TSS_PuzzleRiddle.h"

#include "Objects/TSS_PuzzlePiece.h"


// Sets default values
APuzzleRiddle::APuzzleRiddle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Mesh->SetNotifyRigidBodyCollision(true);
	this->Mesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
}

const USceneComponent* APuzzleRiddle::Interact_Implementation()
{
	return Super::Interact_Implementation();
}

// Called when the game starts or when spawned
void APuzzleRiddle::BeginPlay()
{
	Super::BeginPlay();

	// The locations for the pieces to solve the puzzle
	if (this->PieceLocations.Num() == 0)
	{
		this->PieceLocations.Add(FVector(12.441857, -16.871005, 0.5));
		this->PieceLocations.Add(FVector(-9.410215, -10.403937, 0.5));
		this->PieceLocations.Add(FVector(13.727427, 9.335097, 0.5));
		this->PieceLocations.Add(FVector(6.933628, 16.886237, 0.5));
		this->PieceLocations.Add(FVector(1.845227, 7.947327, 0.5));
		this->PieceLocations.Add(FVector(14.608934, -5.14645, 0.5));
		this->PieceLocations.Add(FVector(18.728416, -12.720832, 0.5));
		this->PieceLocations.Add(FVector(-14.132958, -17.091088, 0.5));
		this->PieceLocations.Add(FVector(2.822082, -6.307995, 0.5));
		this->PieceLocations.Add(FVector(-1.267274, -15.700497, 0.5));
		this->PieceLocations.Add(FVector(-13.897348, -8.331063, 0.5));
		this->PieceLocations.Add(FVector(-12.908943, 15.786153, 0.5));
		this->PieceLocations.Add(FVector(-14.038683,5.442224, 0.5));
		this->PieceLocations.Add(FVector(-9.403979, 3.043186, 0.5));
	}

	int Index = 0;
	// Spawn the pieces from the array
	for (TSubclassOf<APuzzlePiece> Piece : this->Pieces)
	{
		if (Piece == nullptr) continue;
		const FVector Location = this->GetActorLocation();
		
		APuzzlePiece* NewPiece = GetWorld()->SpawnActor<APuzzlePiece>(Piece);
		NewPiece->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		
		// Set random position within +- 16 units of the board
		float RandomX = FMath::RandRange(-16, 16);
		float RandomY = FMath::RandRange(-16, 16);

		RandomX += Location.X;
		RandomY += Location.Y;

		NewPiece->SetActorLocation(FVector(RandomX, RandomY, Location.Z + 0.5f));

		NewPiece->SetLockPosition(this->GetActorLocation() + this->PieceLocations[Index]);

		Index++;
	}
}