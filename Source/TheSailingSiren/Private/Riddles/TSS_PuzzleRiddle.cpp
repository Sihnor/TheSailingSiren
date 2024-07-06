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

	// Spawn the pieces from the array
	for (TSubclassOf<APuzzlePiece> Piece : this->Pieces)
	{
		if (Piece == nullptr) continue; 
		APuzzlePiece* NewPiece = GetWorld()->SpawnActor<APuzzlePiece>(Piece);
		NewPiece->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		// Set the piece's location and rotation to the board's location and rotation
		NewPiece->SetActorLocation(this->GetActorLocation());
		NewPiece->SetActorRotation(this->GetActorRotation());

		if(GEngine)	
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Piece Location: %s"), *NewPiece->GetActorLocation().ToString()));
		}

		//print GetActorLocation
		if(GEngine)	
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Location: %s"), *this->GetActorLocation().ToString()));
		}
	}
	
	
	//for (int i = 0; i < 14; i++)
	//{
	//	APuzzlePiece* Piece = GetWorld()->SpawnActor<APuzzlePiece>(APuzzlePiece::StaticClass());
	//	//Piece->SetMesh(this->PieceMeshes[i]);
	//	Piece->SetActorLocation(FVector(40 - i * 6, -40, 0));
	//	Piece->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	//	Piece->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	//	this->Pieces.Add(Piece);
	//}
}

void APuzzleRiddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
