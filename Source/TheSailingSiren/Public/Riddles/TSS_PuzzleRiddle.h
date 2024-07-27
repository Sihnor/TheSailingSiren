// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Riddles/TSS_RiddleObject.h"
#include "TSS_PuzzleRiddle.generated.h"

class APuzzlePiece;

UCLASS()
class THESAILINGSIREN_API APuzzleRiddle : public ARiddleObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzleRiddle();
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Piece")
	TArray<TSubclassOf<APuzzlePiece>>  Pieces;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Piece")
	TArray<FVector> PieceLocations;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual const USceneComponent* Interact_Implementation() override;

private:
	// Piece number and the rotation of the piece
	TMap<int32, FRotator> RightPieceState;
	
};
