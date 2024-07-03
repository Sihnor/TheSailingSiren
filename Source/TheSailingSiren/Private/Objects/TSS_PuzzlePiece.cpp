// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TSS_PuzzlePiece.h"


// Sets default values
APuzzlePiece::APuzzlePiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = this->Root;

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzlePieceMesh"));
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

void APuzzlePiece::SetMesh(UStaticMesh* Element)
{
	this->Mesh->SetStaticMesh(Element);
}

