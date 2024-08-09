// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TSS_RiddleInteractable.generated.h"

class UCameraComponent;
// This class does not need to be modified.
UINTERFACE()
class URiddleInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THESAILINGSIREN_API IRiddleInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	const USceneComponent*  Interact();

	virtual void StopRiddle() = 0;
};
