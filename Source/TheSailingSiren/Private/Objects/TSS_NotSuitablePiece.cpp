// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TSS_NotSuitablePiece.h"


// Sets default values
ANotSuitablePiece::ANotSuitablePiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = this->Root;

	this->PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PieceMesh"));
	this->PieceMesh->SetupAttachment(this->Root);

	this->PieceMesh->SetNotifyRigidBodyCollision(true);
	this->PieceMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);

	this->PieceMesh->SetGenerateOverlapEvents(true);
	this->PieceMesh->SetCollisionObjectType(ECC_WorldDynamic);
	this->PieceMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	this->PieceMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	this->PieceMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	this->PieceMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);

	this->PieceMesh->OnClicked.AddDynamic(this, &ANotSuitablePiece::OnClicked);
}

void ANotSuitablePiece::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (!this->bIsRightPiece)
	{
		this->OnWrongPieceFound.Broadcast();
	}
}
