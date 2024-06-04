// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheSailingSiren : ModuleRules
{
	public TheSailingSiren(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
