﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TSS_RiddleObject.h"
#include "BirdcageRiddle.generated.h"

UCLASS()
class THESAILINGSIREN_API ABirdcageRiddle : public ARiddleObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABirdcageRiddle();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BirdcageDoor")
	UStaticMeshComponent* BirdcageDoor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual const USceneComponent* Interact_Implementation() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};