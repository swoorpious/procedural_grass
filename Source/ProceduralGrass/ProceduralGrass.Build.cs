// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProceduralGrass : ModuleRules
{
	public ProceduralGrass(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
				"ProceduralGrass",
			}
		);


		PrivateIncludePaths.AddRange(
			new string[]
			{
			}
		);

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"RenderCore",
			"RHI",
			"RHICore",
			
		});
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Landscape",
			"RHI",
			"RenderCore",
			"Renderer",
			"RHICore",
		});
	}
}
