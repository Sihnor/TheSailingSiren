// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TSS_JumpPosition.generated.h"

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
	FVector GetPosition() const { return NewPosition; }

	UFUNCTION(BlueprintCallable)
	void LockPosition(FVector lockPosition)
	{
		this->LockedPosition = lockPosition;
	}
	
	UFUNCTION(BlueprintCallable)
	void SetPosition()
	{
		this->NewPosition = this->LockedPosition;
		OnPositionChanged.Broadcast();
	}

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivate= "true"))
	FVector NewPosition;

	UPROPERTY(EditAnywhere, meta = (AllowPrivate= "true"))
	FVector LockedPosition;
};
