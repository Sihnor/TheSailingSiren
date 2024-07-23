// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TSS_CharacterState.generated.h"

class ICollectibleItem;
/**
 * 
 */
UCLASS()
class THESAILINGSIREN_API ACharacterState : public APlayerState
{
	GENERATED_BODY()

	ACharacterState();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<TScriptInterface<ICollectibleItem>> Inventory;

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemToInventory(TScriptInterface<ICollectibleItem> Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<TScriptInterface<ICollectibleItem>> GetInventory() const { return this->Inventory; }
	
public:
	bool IsInRiddle() const { return this->bIsInRiddle; }
	void SetIsInRiddle(const bool NewState)
	{
		this->bIsInTransition = false;
		
		this->bIsInRiddle = NewState;
	}

	bool IsInDialogue() const { return this->bIsInDialogue; }
	void SetIsInDialogue(const bool NewState)
	{
		this->bIsInTransition = false;
		
		this->bIsInDialogue = NewState;
	}
	
	bool IsInLooking() const { return this->bIsInLooking; }
	void SetIsInLooking(const bool NewState)
	{
		this->bIsInTransition = false;
		
		this->bIsInLooking = NewState;
	}

	bool IsInTransition() const {return this->bIsInTransition; }
	void SetIsInTransition(const bool NewState = true)
	{
		this->bIsInRiddle = false;
		this->bIsInDialogue = false;
		this->bIsInLooking = false;
		
		this->bIsInTransition = NewState;
	}

	virtual void Tick(float DeltaSeconds) override;
	
private:
	bool bIsInRiddle = false;
	bool bIsInDialogue = false;
	bool bIsInLooking = false;
	bool bIsInTransition;
};
