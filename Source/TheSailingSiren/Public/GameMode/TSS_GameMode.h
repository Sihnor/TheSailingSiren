// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TSS_GameMode.generated.h"

class ARiddleObject;
enum class ECurrentPlayState : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartIndoduction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndIndoduction);

UCLASS(minimalapi)
class ATheSailingSirenGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnStartIntroduction();
	virtual void OnStartIntroduction_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GameProgres")
	void OnEndIntroduction();
	virtual void OnEndIntroduction_Implementation();

	UFUNCTION(BlueprintCallable)
	void DelayMotSound();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnMotNoise();
	virtual void OnMotNoise_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnStartFirstDialogueMotAndSamael();
	virtual void OnStartFirstDialogueMotAndSamael_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnStartRiddleOne();
	virtual void OnStartRiddleOne_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnStartFindTranslation();
	virtual void OnStartFindTranslation_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnStartRiddleTwo();
	virtual void OnStartRiddleTwo_Implementation();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnStartSecondDialogueMotAndSamael();
	virtual void OnStartSecondDialogMotAndSamael_Implementation();

	UFUNCTION(BlueprintCallable)
	void PlayDoorSound();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnStartRiddleThreeAndFour();
	virtual void OnStartRiddleThreeAndFour_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnOpenTrapdoor();
	virtual void OnOpenTrapdoor_Implementation();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnCollectLetter();
	virtual void OnCollectLetter_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnReadLetter();
	virtual void OnReadLetter_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnLastDialogueMotAndSamael();
	virtual void OnLastDialogueMotAndSamael_Implementation();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnMonologueMot();
	virtual void OnMonologueMot_Implementation();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GameProgres")
	void OnMonologueSamael();
	virtual void OnMonologueSamael_Implementation();


	UFUNCTION(BlueprintCallable)
	void StartFirstDialogue();

	UFUNCTION(BlueprintCallable)
	void StartSecondDialogue();
	
	

	
	
private:
	UPROPERTY(EditAnywhere, Category = "Riddles", meta = (AllowPrivateAccess = "true"))
	TArray<TSoftObjectPtr<ARiddleObject>> AllRiddles;

	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	ECurrentPlayState CurrentPlayState;

public:
	UFUNCTION(BlueprintCallable)
	ECurrentPlayState GetCurrentPlayState() const { return this->CurrentPlayState; }
	
public:
	ATheSailingSirenGameMode();


public:
	UFUNCTION(BlueprintNativeEvent, Category = "GameProgres")
	void OnRiddleSolved(ECurrentPlayState CurrentRiddleIndex);
	void OnRiddleSolved_Implementation(ECurrentPlayState CurrentRiddleIndex);
};



