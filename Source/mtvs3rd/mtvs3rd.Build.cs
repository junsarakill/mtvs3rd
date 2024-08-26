// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class mtvs3rd : ModuleRules
{
	public mtvs3rd(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
