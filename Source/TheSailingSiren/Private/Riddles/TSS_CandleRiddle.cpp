// Fill out your copyright notice in the Description page of Project Settings.


#include "Riddles/TSS_CandleRiddle.h"

#include "Objects/TSS_CandlePiece.h"


// Sets default values
ACandleRiddle::ACandleRiddle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool ACandleRiddle::NotifyCandleLit(int Index)
{
	if (this->LitCandles == Index)
	{
		this->LitCandles++;
		return true;
	}
	
	this->LitCandles = 0;
	this->OnRiddleUpdate.Broadcast();

	return false;
}

// Called when the game starts or when spawned
void ACandleRiddle::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < Candles.Num(); i++)
	{
		this->Candles[i]->ConnectRiddle(this, i);
	}
}

// Called every frame
void ACandleRiddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

