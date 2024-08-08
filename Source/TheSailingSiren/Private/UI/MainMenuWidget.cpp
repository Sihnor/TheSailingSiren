// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"

#include "Components/Button.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (this->PlayButton)
		this->PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayButtonClicked);

	if (this->OptionsButton)
		this->OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnOptionsButtonClicked);

	if (this->ExitButton)
		this->ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitButtonClicked);
}

void UMainMenuWidget::OnPlayButtonClicked_Implementation()
{
}

void UMainMenuWidget::OnOptionsButtonClicked_Implementation()
{
}

void UMainMenuWidget::OnExitButtonClicked_Implementation()
{
}
