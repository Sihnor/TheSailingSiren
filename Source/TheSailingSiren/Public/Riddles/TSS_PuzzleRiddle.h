// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/TSS_RiddleObject.h"
#include "TSS_PuzzleRiddle.generated.h"

class APuzzlePiece;

UCLASS()
class THESAILINGSIREN_API APuzzleRiddle : public AActor, public IRiddleInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzleRiddle();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BoardMesh")
	UStaticMeshComponent* BoardMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* CameraPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Piece")
	TArray<TSubclassOf<APuzzlePiece>>  Pieces;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Piece")
	TArray<FVector> PieceLocations;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual const USceneComponent* Interact_Implementation() override;

private:
	// Piece number and the rotation of the piece
	TMap<int32, FRotator> RightPieceState;
	
};
