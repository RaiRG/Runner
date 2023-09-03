// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RunnerEditorTarget : TargetRules
{
	public RunnerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] { "Runner" });
	}
}