﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TSS_Interact.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteract : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THESAILINGSIREN_API IInteract
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	void Interact();
};