﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TSS_CharacterController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/TSS_Character.h"
#include "Character/TSS_CharacterState.h"
#include "Interfaces/TSS_CollectibleItem.h"
#include "Interfaces/TSS_RiddleInteractable.h"
#include "TimerManager.h"

void ACharacterController::ResetIsCollecting()
{ { this->bIsCollecting = false; }
}

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

	GetPlayerState<ACharacterState>()->SetIsInLooking(true);
}

void ACharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto CharacterState = GetPlayerState<ACharacterState>();
	
	if (!FMath::IsNearlyEqual(this->ControlRotation.Yaw, this->TargetCameraRotation.Yaw, 0.1f))
	{
		CinematicCameraMovement(DeltaSeconds);
	}
	
	if (CharacterState->IsInDialogue())
	{
		
	}

	if(CharacterState->IsInLooking())
	{
		if (!FMath::IsNearlyEqual(this->ControlRotation.Yaw, this->TargetCameraRotation.Yaw, 0.1f))
		{
			CinematicCameraMovement(DeltaSeconds);
		}
	}

	if(CharacterState->IsInRiddle())
	{
		// On ESCAPE key press
		if (this->WasInputKeyJustPressed(EKeys::Escape))
		{
			StartCameraToPlayerMovement();
		}
	}

	if(CharacterState->IsInTransition())
	{
		if (!FMath::IsNearlyEqual(this->ControlRotation.Yaw, this->TargetCameraRotation.Yaw, 0.1f))
		{
			CinematicCameraMovement(DeltaSeconds);
		}
		else
		{
		}
	}
}

void ACharacterController::StartMove()
{
	this->bIsWalking = true;
}

void ACharacterController::StopMove()
{
	this->bIsWalking = false;
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &ACharacterController::StartMove);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACharacterController::StopMove);

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
			AActor* HitActor = HitResult.GetActor();
			
			if (IRiddleInteractable* InteractableObject = Cast<IRiddleInteractable>(HitActor))
			{
				if (const USceneComponent* PuzzleCamera = InteractableObject->Execute_Interact(HitActor))
					StartCameraToPuzzleMovement(PuzzleCamera->GetComponentLocation(), PuzzleCamera->GetComponentRotation());
			}

			if(Cast<ICollectibleItem>(HitActor))
			{
				CollectItem(HitActor);
				this->bIsCollecting = true;
				
				FTimerHandle Handle;
				FTimerDelegate Delegate;
				Delegate.BindUObject(this, &ACharacterController::ResetIsCollecting);
				GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, 1.0f, false);
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

void ACharacterController::CinematicCameraMovement(const float DeltaTime)
{
	// Normalize the current and target rotations
	FRotator CurrentRotation = this->ControlRotation.GetNormalized();
	FRotator TargetRotation = this->TargetCameraRotation.GetNormalized();

	// Convert to quaternions for smoother interpolation
	FQuat CurrentQuat = FQuat(CurrentRotation);
	FQuat TargetQuat = FQuat(TargetRotation);

	// Interpolate between the quaternions
	FQuat NewQuat = FQuat::Slerp(CurrentQuat, TargetQuat, this->InterpSpeed * DeltaTime);

	// Convert back to rotator
	FRotator NewRotation = NewQuat.Rotator();

	// Apply the new rotation
	this->ControlRotation = NewRotation;
}

void ACharacterController::StartCameraToPuzzleMovement(const FVector& TargetPosition, const FRotator& TargetRotation)
{
	GetPlayerState<ACharacterState>()->SetIsInTransition();

	ATheSailingSirenCharacter* MyCharacter = Cast<ATheSailingSirenCharacter>(this->GetCharacter());

	if (!MyCharacter) return;

	MyCharacter->GetCurrentCameraTransform(this->SavedCameraPosition, this->SavedCameraRotation);
	this->TargetCameraPosition = TargetPosition;
	this->TargetCameraRotation = TargetRotation;

	this->bEnableClickEvents = true;

	this->DisableInput(this);

	MyCharacter->StartMovementCameraToTarget(TargetCameraPosition);
	MyCharacter->OnCameraMovementFinished.AddDynamic(this, &ACharacterController::StopCameraToPuzzleMovement);
}

void ACharacterController::StopCameraToPuzzleMovement()
{
	if (ATheSailingSirenCharacter* MyCharacter = Cast<ATheSailingSirenCharacter>(this->GetCharacter()))
		MyCharacter->OnCameraMovementFinished.RemoveDynamic(this, &ACharacterController::StopCameraToPuzzleMovement);
	
	GetPlayerState<ACharacterState>()->SetIsInRiddle(true);
	
	this->bEnableClickEvents = true;
}

void ACharacterController::StartCameraToPlayerMovement()
{
	GetPlayerState<ACharacterState>()->SetIsInTransition();
	
	this->TargetCameraPosition = this->SavedCameraPosition;
	this->TargetCameraRotation = this->SavedCameraRotation;
	
	if (ATheSailingSirenCharacter* MyCharacter = Cast<ATheSailingSirenCharacter>(this->GetCharacter()))
	{
		MyCharacter->StartMovementCameraToTarget(TargetCameraPosition);
		MyCharacter->OnCameraMovementFinished.AddDynamic(this, &ACharacterController::StopCameraToPlayerMovement);
	}
}

void ACharacterController::StopCameraToPlayerMovement()
{
	if (ATheSailingSirenCharacter* MyCharacter = Cast<ATheSailingSirenCharacter>(this->GetCharacter()))
		MyCharacter->OnCameraMovementFinished.RemoveDynamic(this, &ACharacterController::StopCameraToPlayerMovement);
	
	GetPlayerState<ACharacterState>()->SetIsInLooking(true);
	
	this->bEnableClickEvents = false;

	this->EnableInput(this);
}

void ACharacterController::CollectItem(AActor* Item) const
{
	if (ICollectibleItem* CollectibleItem = Cast<ICollectibleItem>(Item))
	{
		ACharacterState* CharacterState = GetPlayerState<ACharacterState>();
		if(CharacterState)
		{
			CharacterState->AddItemToInventory(Item);
		}
		
		CollectibleItem->Collect();
	}
}
