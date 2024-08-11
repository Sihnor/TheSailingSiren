// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSS_BirdCageOverlay.generated.h"

class UImage;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCageSolved);

/**
 * 
 */
UCLASS()
class THESAILINGSIREN_API UBirdCagePuzzle : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Puzzle")
	TArray<UTexture*> TextureList;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "Puzzle")
	FOnCageSolved OnCageSolved;

public:
	virtual void NativeConstruct() override;

protected:
#pragma  region ImageOne
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UImage* ImageOne;

	UPROPERTY(meta = (BindWidget))
	UButton* ImageOneUp;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ImageOneUpClicked();

	UPROPERTY(meta = (BindWidget))
	UButton* ImageOneDown;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ImageOneDownClicked();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Puzzle")
	int32 ImageOneIndex = 0;
#pragma endregion

#pragma region ImageTwo
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UImage* ImageTwo;

	UPROPERTY(meta = (BindWidget))
	UButton* ImageTwoUp;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ImageTwoUpClicked();

	UPROPERTY(meta = (BindWidget))
	UButton* ImageTwoDown;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ImageTwoDownClicked();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Puzzle")
	int32 ImageTwoIndex = 0;
#pragma endregion

#pragma region ImageThree
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UImage* ImageThree;

	UPROPERTY(meta = (BindWidget))
	class UButton* ImageThreeUp;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ImageThreeUpClicked();

	UPROPERTY(meta = (BindWidget))
	UButton* ImageThreeDown;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ImageThreeDownClicked();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Puzzle")
	int32 ImageThreeIndex = 0;
#pragma endregion

#pragma region ImageFour
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UImage* ImageFour;

	UPROPERTY(meta = (BindWidget))
	UButton* ImageFourUp;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ImageFourDownClicked();

	UPROPERTY(meta = (BindWidget))
	UButton* ImageFourDown;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ImageFourUpClicked();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Puzzle")
	int32 ImageFourIndex = 0;
#pragma endregion

private:
	void CheckPuzzle();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsSolved = false;
};
