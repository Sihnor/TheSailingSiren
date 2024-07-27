// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TSS_Interactable.h"
#include "TSS_InteractableObject.generated.h"

UCLASS()
class THESAILINGSIREN_API AInteractableObject : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableObject();

	public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh;

public:
	UFUNCTION()
	void OnMeshClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);

	UFUNCTION(BlueprintNativeEvent , Category = "Interact")
	void Interact();
	
};
