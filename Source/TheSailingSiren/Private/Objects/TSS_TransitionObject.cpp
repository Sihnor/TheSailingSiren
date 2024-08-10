// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TSS_TransitionObject.h"


// Sets default values
ATransitionObject::ATransitionObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(this->Root);

	this->TransitionPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TransitionPoint"));
	this->TransitionPoint->SetupAttachment(this->Root);

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->Mesh->SetupAttachment(this->Root);
	this->Mesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	this->Mesh->SetGenerateOverlapEvents(true);
	this->Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	this->Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	this->Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	this->Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	this->Mesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
}

void ATransitionObject::UnlockDoor()
{
	this->bIsLocked = false;
}

USceneComponent* ATransitionObject::GetTransitionPoint_Implementation()
{
	if (this->bIsLocked) return nullptr;
	return this->TransitionPoint;
}

// Called when the game starts or when spawned
void ATransitionObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATransitionObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

