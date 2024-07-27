// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TSS_RiddleInteractable.h"
#include "TSS_RiddleObject.generated.h"

UCLASS()
class THESAILINGSIREN_API ARiddleObject : public AActor, public IRiddleInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARiddleObject();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoardMesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* CameraPosition;

public:
	virtual const USceneComponent* Interact_Implementation() override;
};
