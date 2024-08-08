// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TSS_Item.h"
#include "Engine/Texture.h"


// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = this->Root;

	this->ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	this->ItemMesh->SetupAttachment(this->Root);

	this->ItemMesh->SetNotifyRigidBodyCollision(true);
	this->ItemMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);

	this->ItemMesh->SetGenerateOverlapEvents(true);
	this->ItemMesh->SetCollisionObjectType(ECC_WorldDynamic);
	this->ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	this->ItemMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	this->ItemMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	this->ItemMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);

	this->ItemMesh->OnClicked.AddDynamic(this, &AItem::OnClicked);
}

void AItem::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Collect();
}

FString AItem::GetItemName()
{
	return this->ItemName;
}

UTexture2D* AItem::GetItemIcon()
{
	return this->ItemIcon;
}

void AItem::Collect()
{
	// print name of item collected
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Collected %s"), *GetItemName()));

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

