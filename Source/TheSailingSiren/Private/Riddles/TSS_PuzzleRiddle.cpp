// Fill out your copyright notice in the Description page of Project Settings.


#include "Riddles/TSS_PuzzleRiddle.h"

#include "Objects/TSS_PuzzlePiece.h"


// Sets default values
APuzzleRiddle::APuzzleRiddle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = this->Root;

	this->BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));
	this->BoardMesh->SetupAttachment(this->Root);

	this->CameraPosition = CreateDefaultSubobject<USceneComponent>(TEXT("CameraPosition"));
	this->CameraPosition->SetupAttachment(this->Root);
	this->CameraPosition->SetRelativeLocation(FVector(0.f, 0.f, 90.f));

	
	BoardMesh->SetNotifyRigidBodyCollision(true);
	BoardMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
}

const USceneComponent* APuzzleRiddle::Interact_Implementation()
{
	return this->CameraPosition;
}

// Called when the game starts or when spawned
void APuzzleRiddle::BeginPlay()
{
	Super::BeginPlay();

	if (this->PieceLocations.Num() == 0)
	{
		this->PieceLocations.Add(FVector(-17.5, -12.5, 0));
		this->PieceLocations.Add(FVector(-11, 9.16, 0));
		this->PieceLocations.Add(FVector(8.5, -14, 0));
		this->PieceLocations.Add(FVector(16.5, -6.8, 0));
		this->PieceLocations.Add(FVector(7.57, -2.15, 0));
		this->PieceLocations.Add(FVector(-6, -14.8, 0));
		this->PieceLocations.Add(FVector(-13.5, -19, 0));
		this->PieceLocations.Add(FVector(-17.5, 14.16, 0));
		this->PieceLocations.Add(FVector(-6.7, -2.8, 0));
		this->PieceLocations.Add(FVector(-16.25, 1.3, 0));
		this->PieceLocations.Add(FVector(-9, 13.3, 0));
		this->PieceLocations.Add(FVector(15.3, 12.9, 0));
		this->PieceLocations.Add(FVector(4.82, 13.7, 0));
		this->PieceLocations.Add(FVector(2.5, 8.9, 0));
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
		

		NewPiece->SetActorLocation(FVector(RandomX, RandomY, Location.Z + 1));
		NewPiece->SetActorRotation(this->GetActorRotation());

		// Set the target location for the piece
		NewPiece->SetLockPosition(this->GetActorLocation() + this->PieceLocations[Index]);

		Index++;
	}
}

void APuzzleRiddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
