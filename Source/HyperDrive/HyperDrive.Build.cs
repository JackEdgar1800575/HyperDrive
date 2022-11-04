// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HyperDrive : ModuleRules
{
	public HyperDrive(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "HyperDrivePreComp.h";
		MinFilesUsingPrecompiledHeaderOverride = 1;
		bUseUnity = false;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
