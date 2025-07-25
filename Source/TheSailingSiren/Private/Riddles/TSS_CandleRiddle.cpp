﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Riddles/TSS_CandleRiddle.h"

#include "Objects/TSS_CandlePiece.h"


// Sets default values
ACandleRiddle::ACandleRiddle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACandleRiddle::CheckIfRiddleIsSolved()
{
	for (int i = 0; i < Candles.Num() - 1; i++)
	{
		if (!Candles[i]->GetIsLit())
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Candle %d is not lit!"), i));
			return;
		}
	}

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Riddle Solved!"));
	this->OnRiddleSolved.Broadcast(GetRiddleIndex());
}

bool ACandleRiddle::NotifyCandleLit(const int Index)
{
	if (this->LitCandles == Index)
	{
		this->LitCandles++;
		CheckIfRiddleIsSolved();
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
