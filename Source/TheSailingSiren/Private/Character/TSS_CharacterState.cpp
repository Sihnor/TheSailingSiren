// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TSS_CharacterState.h"

#include "Interfaces/TSS_CollectibleItem.h"

ACharacterState::ACharacterState()
{
	PrimaryActorTick.bCanEverTick = true;
	
	this->bIsInRiddle = false;
	this->bIsInDialogue = false;
	this->bIsInLooking = false;
	this->bIsInTransition = false;
}

void ACharacterState::AddItemToInventory(const TScriptInterface<ICollectibleItem> Item)
{
	this->Inventory.Add(Item);
}

void ACharacterState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, .1f, FColor::Red, TEXT("Inventory:"));
	
	for (auto Element : this->Inventory)
	{
		// print name of the item
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, .1f, FColor::Red, Element->GetItemName());
	}
}
