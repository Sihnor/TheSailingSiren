// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TSS_Transition.h"
#include "TSS_TransitionObject.generated.h"

UCLASS()
class THESAILINGSIREN_API ATransitionObject : public AActor, public ITransition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* TransitionPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable)
	void UnlockDoor();
	
public:
	virtual USceneComponent* GetTransitionPoint_Implementation() override;

public:
	// Sets default values for this actor's properties
	ATransitionObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bIsLocked = true;
};
