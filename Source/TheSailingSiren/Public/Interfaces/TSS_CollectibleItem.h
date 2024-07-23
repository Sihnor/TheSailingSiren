// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TSS_CollectibleItem.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCollectibleItem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THESAILINGSIREN_API ICollectibleItem
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FString GetItemName() = 0;
	
	virtual void Collect() = 0;
};
