// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TSS_RiddleObject.h"
#include "TSS_NotSuitableRiddle.generated.h"

UCLASS()
class THESAILINGSIREN_API ANotSuitableRiddle : public ARiddleObject
{
	GENERATED_BODY()

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
};
