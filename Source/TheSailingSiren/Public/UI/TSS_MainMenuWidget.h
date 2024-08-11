// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSS_MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class THESAILINGSIREN_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* PlayButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* OptionsButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* ExitButton;

public:
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnPlayButtonClicked"))
	void OnPlayButtonClicked();
	void OnPlayButtonClicked_Implementation();
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnOptionsButtonClicked"))
	void OnOptionsButtonClicked();
	void OnOptionsButtonClicked_Implementation();
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnExitButtonClicked"))
	void OnExitButtonClicked();
	void OnExitButtonClicked_Implementation();
};
