// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Runner : ModuleRules
{
	public Runner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"GameplayTasks",
			"NavigationSystem",
			"AIModule"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new[]
		{
			"Runner/Public/Player",
			"Runner/Public/InteractableObjects",
			"Runner/Public/Interfaces",
			"Runner/Public/AI",
			"Runner/Public/AI/Decorators",
			"Runner/Public/AI/Tasks",
			"Runner/Public/AI/EQS",
			"Runner/Public/AI/Services"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}