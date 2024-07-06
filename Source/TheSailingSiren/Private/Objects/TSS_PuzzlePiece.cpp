// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TSS_PuzzlePiece.h"


// Sets default values
APuzzlePiece::APuzzlePiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = this->Root;
	
	this->BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzlePieceMesh"));
	this->BoardMesh->SetupAttachment(this->Root);
	
	this->BoardMesh->SetNotifyRigidBodyCollision(true);
	this->BoardMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);

	this->BoardMesh->OnReleased.AddDynamic(this, &APuzzlePiece::OnRelease);
}

void APuzzlePiece::OnRelease(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Released"));
}

// Called when the game starts or when spawned
void APuzzlePiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzlePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuzzlePiece::SetLockPosition(FVector Position)
{
	this->LockPosition = Position;
}

void APuzzlePiece::LockNearPosition()
{
	// Get the current location of the piece
	FVector CurrentLocation = this->GetActorLocation();
	// Get the distance between the current location and the lock position
	FVector Distance = this->LockPosition - CurrentLocation;
	// If the distance is less than 10 units, lock the piece to the lock position
	if (Distance.Size() < 5.f)
	{
		this->SetActorLocation(this->LockPosition);
	}
}



