// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheCube : ModuleRules
{
	public TheCube(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" , "UMG", "Niagara", "GeometryCollectionEngine" });
	}
}
