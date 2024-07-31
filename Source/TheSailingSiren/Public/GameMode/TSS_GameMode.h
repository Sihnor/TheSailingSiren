// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TSS_GameMode.generated.h"

class ARiddleObject;
enum class ECurrentPlayState : uint8;

UCLASS(minimalapi)
class ATheSailingSirenGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Riddles", meta = (AllowPrivateAccess = "true"))
	TArray<TSoftObjectPtr<ARiddleObject>> AllRiddles;

	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	ECurrentPlayState CurrentPlayState;

public:
	UFUNCTION(BlueprintCallable)
	ECurrentPlayState GetCurrentPlayState() const { return this->CurrentPlayState; }
	
public:
	ATheSailingSirenGameMode();

	
private:
	UFUNCTION()
	void OnRiddleSolved(int CurrentRiddleIndex);

private:
	int CurrenRiddle = 0;
};



