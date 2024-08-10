// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Riddles/TSS_RiddleObject.h"
#include "TSS_CandleRiddle.generated.h"

class AStaticMeshActor;
class ACandlePiece;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRiddleUpdate);

UCLASS()
class THESAILINGSIREN_API ACandleRiddle : public ARiddleObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Riddle")
	TArray<ACandlePiece*> Candles;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Riddle")
	AStaticMeshActor* TrapDoor;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Riddle")
	TArray<AActor*> RewardItems;

	UFUNCTION(BlueprintNativeEvent)
	void MoveRiddleObject();

	UFUNCTION(BlueprintImplementableEvent)
	void OnFinishedRiddle();


	FOnRiddleUpdate OnRiddleUpdate;
public:
	// Sets default values for this actor's properties
	ACandleRiddle();

	void CheckIfRiddleIsSolved();
	bool NotifyCandleLit(int Index);

	virtual const USceneComponent* Interact_Implementation() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int LitCandles = 0;

	bool bIsInRiddle = false;

};
