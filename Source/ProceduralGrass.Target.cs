// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProceduralGrassTarget : TargetRules
{
	public ProceduralGrassTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("ProceduralGrass");
		// RegisterModulesCreatedByRider();
	}

	// private void RegisterModulesCreatedByRider()
	// {
	// 	ExtraModuleNames.AddRange(new string[] { "ProceduralGrassShaders" });
	// }
}
