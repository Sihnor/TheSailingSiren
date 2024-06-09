// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TSS_Interact.h"
#include "TSS_InteractableObject.generated.h"

UCLASS()
class THESAILINGSIREN_API AInteractableObject : public AActor, public IInteract
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent , Category = "Interact")
	void Interact();
	
};
