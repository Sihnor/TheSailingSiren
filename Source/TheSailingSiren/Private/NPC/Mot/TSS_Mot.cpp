// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Mot/TSS_Mot.h"


// Sets default values
AMot::AMot()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = this->Root;
	
	this->Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	this->Mesh->SetupAttachment(this->Root);
	
}

// Called to bind functionality to input
void AMot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

