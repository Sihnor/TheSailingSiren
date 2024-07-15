// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TSS_PlayerPosition.generated.h"

/**
 * 
 */
UCLASS()
class THESAILINGSIREN_API UPlayerPosition : public UDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	FVector GetPlayerPosition() const { return PlayerPosition; }

	void SetPlayerPosition(const FVector& NewPlayerPosition);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FVector PlayerPosition;
};

inline void UPlayerPosition::SetPlayerPosition(const FVector& NewPlayerPosition)
{
	this->PlayerPosition = NewPlayerPosition;
}
