﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TSS_CharacterController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class THESAILINGSIREN_API ACharacterController : public APlayerController
{
	GENERATED_BODY()
	
#pragma region Input

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Start Looking Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* StartLookAction;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Interact Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

#pragma endregion

public:

	UFUNCTION(BlueprintCallable)
	bool GetIsWalking() const { return bIsWalking; }
	
	UFUNCTION(BlueprintCallable)
	bool GetIsCollecting() const { return bIsCollecting; }

	UFUNCTION(BlueprintCallable)
	void ResetIsCollecting();
	

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void StartMove();
	void StopMove();
	virtual void SetupInputComponent() override;
	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	void Interact(const FInputActionValue& InputActionValue);

	void Look(const FInputActionValue& Value);
	
	/** Called to enable looking */
	void StartLooking(const FInputActionValue& InputActionValue);
	void StopLooking(const FInputActionValue& InputActionValue);

private:
	void CenterMouseCursor();

	void CinematicCameraMovement(float DeltaTime);

	void StartCameraToPuzzleMovement(const FVector& TargetPosition, const FRotator& TargetRotation);
	UFUNCTION()
	void StopCameraToPuzzleMovement();
	void StartCameraToPlayerMovement();
	UFUNCTION()
	void StopCameraToPlayerMovement();

	void CollectItem(AActor* Item) const;

private:
	FVector SavedCameraPosition;
	FVector TargetCameraPosition;

	FRotator SavedCameraRotation;	
	FRotator TargetCameraRotation;
	bool bIsLooking = false;
	bool bIsInPuzzleMovement = false;
	float InterpSpeed = 30.0f ;

	float InteractionRange = 300.0f;

	bool bIsCollecting = false;
	bool bIsWalking = false;
};
