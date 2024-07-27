// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TSS_Raven.generated.h"

enum class ECurrentPlayState : uint8;

UCLASS()
class THESAILINGSIREN_API ARaven : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARaven();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Raven", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Raven", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* MeshComponent;

	UFUNCTION()
	void PlayHintForRiddleOne();
	UFUNCTION()
	void PlayHintForRiddleTwo();
	UFUNCTION()
	void PlayHintForRiddleThree();
	UFUNCTION()
	void PlayHintForRiddleFour();
	UFUNCTION()
	void PlayHintForRiddleFive();
	UFUNCTION()
	void OnRavenClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

};
