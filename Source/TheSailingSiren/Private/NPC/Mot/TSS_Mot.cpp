﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Mot/TSS_Mot.h"


// Sets default values
AMot::AMot()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
