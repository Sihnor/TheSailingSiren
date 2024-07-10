// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JumpPosition.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnPositionChanged);

UCLASS()
class THESAILINGSIREN_API UJumpPosition : public UDataAsset
{
	GENERATED_BODY()

public:
	FOnPositionChanged OnPositionChanged;
	
	UFUNCTION(BlueprintCallable)
	FVector GetPosition() const { return Position; }

	UFUNCTION(BlueprintCallable)
	void SetPosition(const FVector NewPosition)
	{
		this->Position = NewPosition;
		OnPositionChanged.Broadcast();
	}

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivate= "true"))
	FVector Position;
};
