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

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	UFUNCTION(BlueprintImplementableEvent)
	void OnCollect();
	
public:
	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	virtual FString GetItemName() override;
	UFUNCTION(BlueprintCallable)
	virtual UTexture2D* GetItemIcon() override;
	
	virtual void Collect() override;
	
public:
	// Sets default values for this actor's properties
	AItem();
};
