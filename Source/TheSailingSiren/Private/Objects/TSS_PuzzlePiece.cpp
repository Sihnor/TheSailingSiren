// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TSS_PuzzlePiece.h"


bool GetLinePlaneIntersection(const FVector& LineStart, const FVector& LineEnd, const FVector& PlanePoint, const FVector& PlaneNormal, FVector& Intersection)
{
	const FVector LineDirection = LineEnd - LineStart;
	if (const float DotProduct = FVector::DotProduct(LineDirection, PlaneNormal); FMath::Abs(DotProduct) > KINDA_SMALL_NUMBER)
	{
		if (const float T = FVector::DotProduct(PlanePoint - LineStart, PlaneNormal) / DotProduct; T >= 0.0f && T <= 1.0f)
		{
			Intersection = LineStart + T * LineDirection;
			return true;
		}
	}
	return false;
}


// Sets default values
APuzzlePiece::APuzzlePiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = this->Root;
	
	this->BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzlePieceMesh"));
	this->BoardMesh->SetupAttachment(this->Root);
	
	this->BoardMesh->SetNotifyRigidBodyCollision(true);
	this->BoardMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);

	this->BoardMesh->SetGenerateOverlapEvents(true);
	this->BoardMesh->SetCollisionObjectType(ECC_WorldDynamic);
	this->BoardMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	this->BoardMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	this->BoardMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	this->BoardMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);

	this->BoardMesh->OnClicked.AddDynamic(this, &APuzzlePiece::OnClicked);
	this->BoardMesh->OnReleased.AddDynamic(this, &APuzzlePiece::OnRelease);
}

void APuzzlePiece::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	this->bStickToMouse = true;

	// Get Moues Position in World Space
	FVector WorldLocation, WorldDirection;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FVector Start = WorldLocation;
	FVector End = WorldLocation + WorldDirection * 1000;

	FHitResult HitResult;

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

	FVector CurrentActorLocation = GetActorLocation();
	
	this->MouseOffset = HitResult.ImpactPoint - CurrentActorLocation;

	CurrentActorLocation.Z += 1;
	SetActorLocation(CurrentActorLocation);
}

void APuzzlePiece::OnRelease(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	FVector CurrentLocation = this->GetActorLocation();
	CurrentLocation.Z -= 1;
	
	SetActorLocation(CurrentLocation);
	
	// if the piece is close to the lock position, lock it
	LockNearPosition();
	this->bStickToMouse = false;
}

// Called when the game starts or when spawned
void APuzzlePiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzlePiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!this->bStickToMouse) return;
	
	// Get Moues Position in World Space
	FVector MousePosition;
	FVector MouseDirection;
	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->DeprojectMousePositionToWorld(MousePosition, MouseDirection);

	const FVector EndPoint = MousePosition + MouseDirection * 1000;

	const FVector PlanePoint = GetActorLocation();
	const FVector PlaneNormal = FVector(0, 0, 1);

	FVector Intersection;

	GetLinePlaneIntersection(MousePosition, EndPoint, PlanePoint, PlaneNormal, Intersection);

	SetActorLocation(Intersection - this->MouseOffset);
}

void APuzzlePiece::SetLockPosition(const FVector& Position)
{
	this->LockPosition = Position;
}

void APuzzlePiece::LockNearPosition()
{
	// Get the current location of the piece
	const FVector CurrentLocation = this->GetActorLocation();
	// Get the distance between the current location and the lock position
	const FVector Distance = this->LockPosition - CurrentLocation;

	// If the distance is less than 10 units, lock the piece to the lock position
	if (Distance.Size() < 5.f)
	{
		this->SetActorLocation(this->LockPosition);
	}
}


