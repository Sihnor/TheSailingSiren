// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TSS_Interactable.h"
#include "TSS_CandlePiece.generated.h"

class ACandleRiddle;

UCLASS()
class THESAILINGSIREN_API ACandlePiece : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* CandleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* LitMaterial;
public:
	// Sets default values for this actor's properties
	ACandlePiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

public:
	UFUNCTION()
	void NotifyCandleLit();
	void ConnectRiddle(ACandleRiddle* Riddle, int Index);


private:
	ACandleRiddle* ConnectedCandlePiece = nullptr;
	int CandleIndex = -1;
	bool bIsLit = false;

	UMaterialInterface* BaseMaterial;
};
