// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HyperDrive : ModuleRules
{
	public HyperDrive(ReadOnlyTargetRules Target) : base(Target)
	{
		MinFilesUsingPrecompiledHeaderOverride = 1;
		bUseUnity = false;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","AkAudio" });
	}
}
