﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TSS_CharacterController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/TSS_Character.h"
#include "Interfaces/TSS_RiddleInteractable.h"

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);

		this->TargetCameraRotation = this->GetControlRotation();
		this->bShowMouseCursor = true;
	}
}

void ACharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Check if the current rotation is equal to the target rotation with tolerance
	if (!FMath::IsNearlyEqual(this->GetControlRotation().Yaw, this->TargetCameraRotation.Yaw, 0.1f) && !FMath::IsNearlyEqual(this->GetControlRotation().Pitch, this->TargetCameraRotation.Pitch, 0.1f)) CinematicCameraMovement(DeltaSeconds);
}

void ACharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterController::Move);

		// Start Looking
		EnhancedInputComponent->BindAction(StartLookAction, ETriggerEvent::Started, this, &ACharacterController::StartLooking);
		EnhancedInputComponent->BindAction(StartLookAction, ETriggerEvent::Completed, this, &ACharacterController::StopLooking);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterController::Look);

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACharacterController::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void ACharacterController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = this->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement
	this->GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
	this->GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);
}

void ACharacterController::Interact(const FInputActionValue& InputActionValue)
{
	FVector WorldLocation;
	FVector WorldDirection;
	
	if (this->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FHitResult HitResult;
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, WorldLocation + WorldDirection * this->InteractionRange, ECollisionChannel::ECC_Visibility, CollisionQueryParams))
		{
			if (IRiddleInteractable* InteractableObject = Cast<IRiddleInteractable>(HitResult.GetActor()))
			{
				
				auto PuzzleCamera = InteractableObject->Execute_Interact(HitResult.GetActor());
				if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Interactable Object: %s"), *PuzzleCamera->GetName()));

				StartCameraToPuzzleMovement(PuzzleCamera->GetComponentLocation(), PuzzleCamera->GetComponentRotation());
			}
		}
	}
}

void ACharacterController::Look(const FInputActionValue& Value)
{
	if (!this->bIsLooking) return;

	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	this->TargetCameraRotation = FRotator(this->TargetCameraRotation.Pitch - LookAxisVector.Y, this->TargetCameraRotation.Yaw + LookAxisVector.X, this->TargetCameraRotation.Roll);

	this->CenterMouseCursor();
}

void ACharacterController::CenterMouseCursor()
{
	if (const ULocalPlayer* LocalPlayer = this->GetLocalPlayer(); LocalPlayer && LocalPlayer->ViewportClient)
	{
		const FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
		const FIntPoint ViewportSize = Viewport->GetSizeXY();
		this->SetMouseLocation(ViewportSize.X / 2, ViewportSize.Y / 2);
	}
}

void ACharacterController::StartLooking(const FInputActionValue& InputActionValue)
{
	this->bIsLooking = true;

	this->bShowMouseCursor = false;
}

void ACharacterController::StopLooking(const FInputActionValue& InputActionValue)
{
	this->bIsLooking = false;
	
	this->CenterMouseCursor();

	this->bShowMouseCursor = true;
}

void ACharacterController::CinematicCameraMovement(float DeltaTime)
{
	const float CurrentYaw = this->ControlRotation.Yaw;
	const float TargetYaw = this->TargetCameraRotation.Yaw;
	const float CurrentPitch = this->ControlRotation.Pitch;
	const float TargetPitch = this->TargetCameraRotation.Pitch;
	constexpr float Exponent = 3.0f;

	const float YawValue = FMath::InterpEaseInOut(CurrentYaw, TargetYaw, this->InterpSpeed * DeltaTime, Exponent);
	this->ControlRotation.Yaw = YawValue;

	const float PitchValue = FMath::InterpEaseInOut(CurrentPitch, TargetPitch, this->InterpSpeed * DeltaTime, Exponent);
	this->ControlRotation.Pitch = PitchValue;
}

void ACharacterController::StartCameraToPuzzleMovement(const FVector& TargetPosition, const FRotator& TargetRotation)
{
	this->SavedCameraPosition = this->GetCharacter()->GetActorLocation();
	this->SavedCameraRotation = this->ControlRotation;
	this->TargetCameraPosition = TargetPosition;
	this->TargetCameraRotation = TargetRotation;
	
	this->DisableInput(this);

	if (ATheSailingSirenCharacter* MyCharacter = Cast<ATheSailingSirenCharacter>(this->GetCharacter()))
		MyCharacter->StartMovementCameraToTarget(TargetCameraPosition,TargetRotation);
}

void ACharacterController::StopCameraToPuzzleMovement()
{
}

void ACharacterController::StartCameraToPlayerMovement()
{
	this->TargetCameraPosition = this->SavedCameraPosition;
	this->TargetCameraRotation = this->SavedCameraRotation;
}

void ACharacterController::StopCameraToPlayerMovement()
{
}