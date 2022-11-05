// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HyperDrive : ModuleRules
{
	public HyperDrive(ReadOnlyTargetRules Target) : base(Target)
	{

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
