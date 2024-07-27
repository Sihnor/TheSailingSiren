// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TSS_CollectibleItem.h"
#include "TSS_Item.generated.h"

UCLASS()
class THESAILINGSIREN_API AItem : public AActor, public ICollectibleItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FString ItemName;
	
public:
	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	virtual FString GetItemName() override;
	
	virtual void Collect() override;
	
public:
	// Sets default values for this actor's properties
	AItem();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
