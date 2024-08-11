// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/CurrentPlayState.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TSS_RiddleInteractable.h"
#include "TSS_RiddleObject.generated.h"

enum class ECurrentPlayState : uint8;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRiddleSolved, ECurrentPlayState, CurrentRiddleIndex);

UCLASS()
class THESAILINGSIREN_API ARiddleObject : public AActor, public IRiddleInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARiddleObject();

	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoardMesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* CameraPosition;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Letter")
	AActor* Letter;

public:
	virtual const USceneComponent* Interact_Implementation() override;
	void SetRiddleIndex(const ECurrentPlayState State) { if(this->RiddleState != ECurrentPlayState::None) return; this->RiddleState = State; }
	ECurrentPlayState GetRiddleIndex() const { return this->RiddleState; }

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "Riddle")
	FOnRiddleSolved OnRiddleSolved;

protected:
	ECurrentPlayState RiddleState = ECurrentPlayState::None;

	virtual void StopRiddle() override;
};
