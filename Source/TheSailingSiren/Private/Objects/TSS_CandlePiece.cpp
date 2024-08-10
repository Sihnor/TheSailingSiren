// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TSS_CandlePiece.h"

#include "Riddles/TSS_CandleRiddle.h"


// Sets default values
ACandlePiece::ACandlePiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->RootComponent = this->Root;

	this->CandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CandleMesh"));
	this->CandleMesh->SetupAttachment(this->Root);

	this->CandleMesh->SetNotifyRigidBodyCollision(true);
	this->CandleMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);

	this->CandleMesh->SetGenerateOverlapEvents(true);
	this->CandleMesh->SetCollisionObjectType(ECC_WorldDynamic);
	this->CandleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	this->CandleMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	this->CandleMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	this->CandleMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);

	this->CandleMesh->OnClicked.AddDynamic(this, &ACandlePiece::OnClicked);

	
}

// Called when the game starts or when spawned
void ACandlePiece::BeginPlay()
{
	Super::BeginPlay();

	this->BaseMaterial = this->CandleMesh->GetMaterial(0);
}

void ACandlePiece::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("CandlePiece Clicked!"));
	if(this->bIsLit) return;

	this->bIsLit = this->ConnectedCandlePiece->NotifyCandleLit(this->CandleIndex);

	// Set color green of the candle
	if(this->bIsLit) this->CandleMesh->SetMaterial(0, this->LitMaterial);
}

void ACandlePiece::NotifyCandleLit()
{
	this->bIsLit = false;

	this->CandleMesh->SetMaterial(0, this->BaseMaterial);
}

void ACandlePiece::ConnectRiddle(ACandleRiddle* Riddle, const int Index)
{
	this->ConnectedCandlePiece = Riddle;
	this->ConnectedCandlePiece->OnRiddleUpdate.AddUniqueDynamic(this, &ACandlePiece::NotifyCandleLit);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Connected CandlePiece to Riddle %s"), *Riddle->GetName()));

	this->CandleIndex = Index;
}

