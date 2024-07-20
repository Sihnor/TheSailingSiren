// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TSS_NotSuitablePiece.generated.h"

UCLASS()
class THESAILINGSIREN_API ANotSuitablePiece : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANotSuitablePiece();

public:
	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	
	UFUNCTION()
	void OnRelease(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsRightPiece() const { return this->bIsRightPiece; }

private:

private:
	bool bIsRightPiece = false;
};
