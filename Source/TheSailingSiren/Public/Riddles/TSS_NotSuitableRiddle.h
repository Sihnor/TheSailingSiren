﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TSS_RiddleObject.h"
#include "TSS_NotSuitableRiddle.generated.h"

class ANotSuitablePiece;

UCLASS()
class THESAILINGSIREN_API ANotSuitableRiddle : public ARiddleObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Riddle")
	TSubclassOf<ANotSuitablePiece> Piece;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Riddle")
	TArray<UMaterial*> NotSuitableMaterials;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Riddle")
	TArray<UMaterial*> SuitableMaterials;
	
public:
	// Sets default values for this actor's properties
	ANotSuitableRiddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual const USceneComponent* Interact_Implementation() override;

private:
	void StartRiddle();

	UFUNCTION()
	void StartNextRound();

	bool CheckForAnotherRound();
	
private:
	// The placement of the wrong pieces as binary
	int RightPlaces = 0;
	int RightIndex = 0;

	ANotSuitablePiece* CurrentWrongPiece = nullptr;
	TArray<ANotSuitablePiece*> AllRightPieces;
};