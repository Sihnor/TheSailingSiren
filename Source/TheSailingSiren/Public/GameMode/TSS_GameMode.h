// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TSS_GameMode.generated.h"

enum class ECurrentPlayState : uint8;

UCLASS(minimalapi)
class ATheSailingSirenGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	ECurrentPlayState CurrentPlayState;

public:
	UFUNCTION(BlueprintCallable)
	ECurrentPlayState GetCurrentPlayState() const { return this->CurrentPlayState; }
	
public:
	ATheSailingSirenGameMode();

	
};



