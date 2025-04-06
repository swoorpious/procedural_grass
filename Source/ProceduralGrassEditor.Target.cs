// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProceduralGrassEditorTarget : TargetRules
{
	public ProceduralGrassEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
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
