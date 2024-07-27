// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TSS_RiddleObject.h"
#include "TSS_CandleRiddle.generated.h"

class ACandlePiece;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRiddleUpdate);

UCLASS()
class THESAILINGSIREN_API ACandleRiddle : public ARiddleObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Riddle")
	TArray<ACandlePiece*> Candles;

	FOnRiddleUpdate OnRiddleUpdate;
public:
	// Sets default values for this actor's properties
	ACandleRiddle();

	bool NotifyCandleLit(int Index);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int LitCandles = 0;
};
