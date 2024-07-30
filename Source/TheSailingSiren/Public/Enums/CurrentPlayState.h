// Unreal Engine Enum for the current play state of the game
#pragma once

UENUM(BlueprintType)
enum class ECurrentPlayState : uint8
{
	None,
	RiddleOne,
	RiddleTwo,
	RiddleThree,
	RiddleFour,
	RiddleFive,
	Finished,
};