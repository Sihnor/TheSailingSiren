// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TSS_NotSuitablePiece.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWringPieceFound);

UCLASS()
class THESAILINGSIREN_API ANotSuitablePiece : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANotSuitablePiece();

	FOnWringPieceFound OnWrongPieceFound;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* PieceMesh;

public:
	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetRightPiece(const bool IsRight) { this->bIsRightPiece = IsRight; }
	bool IsRightPiece() const { return this->bIsRightPiece; }
	

private:

private:
	bool bIsRightPiece = true;
};
