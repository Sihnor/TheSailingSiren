// Fill out your copyright notice in the Description page of Project Settings.


#include "TheSailingSiren/Public/Objects/TSS_InteractableObject.h"


// Sets default values
AInteractableObject::AInteractableObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = this->Mesh;

	Mesh->SetNotifyRigidBodyCollision(true);
	Mesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	Mesh->OnClicked.AddDynamic(this, &AInteractableObject::OnMeshClicked);
}

void AInteractableObject::OnMeshClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	Interact();
}

void AInteractableObject::Interact_Implementation()
{
	// print the name
	UE_LOG(LogTemp, Warning, TEXT("Interacted with %s"), *GetName());
}