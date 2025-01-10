// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Skeleton : ModuleRules
{
	public Skeleton(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		PublicDependencyModuleNames.AddRange(new string[] { "AnimGraphRuntime" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[] {
			"Skeleton",
			"Skeleton/Enums",
			"Skeleton/Structs",
			"Skeleton/Interfaces",
			"Skeleton/GameMods",
			"Skeleton/Managers",
			"Skeleton/UI",
			"Skeleton/Components"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
