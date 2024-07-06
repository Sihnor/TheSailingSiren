// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheSailingSiren/Public/Character/TSS_Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATheSailingSirenCharacter

ATheSailingSirenCharacter::ATheSailingSirenCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f; // The camera follows at this distance behind the character
	this->CameraBoom->SocketOffset = FVector(40.f, 40.f, 50.f);
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ATheSailingSirenCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

void ATheSailingSirenCharacter::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(this->bIsCameraMoving)
	{
		this->MoveCameraToTarget(DeltaSeconds);
	}
}

void ATheSailingSirenCharacter::StartMovementCameraToTarget(const FVector& TargetLocation)
{
	this->CameraTargetLocation = TargetLocation;
	this->bIsCameraMoving = true;
}

void ATheSailingSirenCharacter::MoveCameraToTarget(const float DeltaSeconds)
{
	// Move the camera to the target location
	const FVector NewLocation = FMath::VInterpTo(this->FollowCamera->GetComponentLocation(), this->CameraTargetLocation, DeltaSeconds, 2.0f);
	
	this->FollowCamera->SetWorldLocation(NewLocation);

	if(FVector::Distance(this->FollowCamera->GetComponentLocation(), this->CameraTargetLocation) < 0.5f)
	{
		this->FollowCamera->SetWorldLocation(this->CameraTargetLocation);
		this->bIsCameraMoving = false;
	}
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATheSailingSirenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}