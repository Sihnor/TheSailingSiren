// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TSS_PuzzlePiece.generated.h"

UCLASS()
class THESAILINGSIREN_API APuzzlePiece : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzlePiece();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* BoardMesh;

	UFUNCTION()
	void OnRelease(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetPieceNumber(int32 Number) { this->PieceNumber = Number; }
	void SetPieceRotation(FRotator Rotation) { this->PieceRotation = Rotation; }

	int32 GetPieceNumber() const { return this->PieceNumber; }
	FRotator GetPieceRotation() const { return this->PieceRotation; }

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLockPosition(FVector Position);
	void LockNearPosition();

private:
	// Piece number and the rotation of the piece
	int32 PieceNumber;
	FRotator PieceRotation;

	FVector LockPosition;
};
