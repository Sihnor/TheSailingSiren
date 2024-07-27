// Fill out your copyright notice in the Description page of Project Settings.


#include "Riddles/TSS_BirdCageRiddle.h"

#include "Components/Button.h"

void UBirdCagePuzzle::NativeConstruct()
{
	Super::NativeConstruct();

	this->ImageOneUp->OnClicked.AddDynamic(this, &UBirdCagePuzzle::ImageOneUpClicked);
	this->ImageOneDown->OnClicked.AddDynamic(this, &UBirdCagePuzzle::ImageOneDownClicked);
	this->ImageTwoUp->OnClicked.AddDynamic(this, &UBirdCagePuzzle::ImageTwoUpClicked);
	this->ImageTwoDown->OnClicked.AddDynamic(this, &UBirdCagePuzzle::ImageTwoDownClicked);
	this->ImageThreeUp->OnClicked.AddDynamic(this, &UBirdCagePuzzle::ImageThreeUpClicked);
	this->ImageThreeDown->OnClicked.AddDynamic(this, &UBirdCagePuzzle::ImageThreeDownClicked);
	this->ImageFourUp->OnClicked.AddDynamic(this, &UBirdCagePuzzle::ImageFourUpClicked);
	this->ImageFourDown->OnClicked.AddDynamic(this, &UBirdCagePuzzle::ImageFourDownClicked);
}

void UBirdCagePuzzle::ImageOneUpClicked_Implementation()
{
	this->ImageOneIndex++;
	if (this->ImageOneIndex >= this->TextureList.Num()) this->ImageOneIndex = 0;

	CheckPuzzle();
}

void UBirdCagePuzzle::ImageOneDownClicked_Implementation()
{
	this->ImageOneIndex--;
	if (this->ImageOneIndex < 0) this->ImageOneIndex = this->TextureList.Num() - 1;

	CheckPuzzle();
}

void UBirdCagePuzzle::ImageTwoUpClicked_Implementation()
{
	this->ImageTwoIndex++;
	if (this->ImageTwoIndex >= this->TextureList.Num()) this->ImageTwoIndex = 0;

	CheckPuzzle();
}

void UBirdCagePuzzle::ImageTwoDownClicked_Implementation()
{
	this->ImageTwoIndex--;
	if (this->ImageTwoIndex < 0) this->ImageTwoIndex = this->TextureList.Num() - 1;

	CheckPuzzle();
}

void UBirdCagePuzzle::ImageThreeUpClicked_Implementation()
{
	this->ImageThreeIndex++;
	if (this->ImageThreeIndex >= this->TextureList.Num()) this->ImageThreeIndex = 0;

	CheckPuzzle();
}


void UBirdCagePuzzle::ImageThreeDownClicked_Implementation()
{
	this->ImageThreeIndex--;
	if (this->ImageThreeIndex < 0) this->ImageThreeIndex = this->TextureList.Num() - 1;

	CheckPuzzle();
}

void UBirdCagePuzzle::ImageFourUpClicked_Implementation()
{
	this->ImageFourIndex++;
	if (this->ImageFourIndex >= this->TextureList.Num()) this->ImageFourIndex = 0;

	CheckPuzzle();
}

void UBirdCagePuzzle::ImageFourDownClicked_Implementation()
{
	this->ImageFourIndex--;
	if (this->ImageFourIndex < 0) this->ImageFourIndex = this->TextureList.Num() - 1;

	CheckPuzzle();
}

void UBirdCagePuzzle::CheckPuzzle()
{
	if (ImageOneIndex == 14 && ImageTwoIndex == 15 && this->ImageThreeIndex == 4 && this->ImageFourIndex == 13)
	{
		this->ImageOneUp->SetVisibility(ESlateVisibility::Hidden);
		this->ImageOneDown->SetVisibility(ESlateVisibility::Hidden);
		this->ImageTwoUp->SetVisibility(ESlateVisibility::Hidden);
		this->ImageTwoDown->SetVisibility(ESlateVisibility::Hidden);
		this->ImageThreeUp->SetVisibility(ESlateVisibility::Hidden);
		this->ImageThreeDown->SetVisibility(ESlateVisibility::Hidden);
		this->ImageFourUp->SetVisibility(ESlateVisibility::Hidden);
		this->ImageFourDown->SetVisibility(ESlateVisibility::Hidden);
	}
}
