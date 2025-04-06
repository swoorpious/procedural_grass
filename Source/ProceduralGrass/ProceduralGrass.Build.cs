// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
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
				Path.Combine(GetModuleDirectory("Renderer"), "Private")
			}
		);


		PrivateIncludePaths.AddRange(
			new string[]
			{
			}
		);

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject",
			"Engine",
			"Projects",
			"RHI", 
			"Renderer",
			"RenderCore",
			
		});
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"Engine",
			
			"CoreUObject",
			"InputCore",
			"EnhancedInput",
			"Landscape",
			
			"RHI",
			"RenderCore",
			"Renderer",
			"RHICore",

			// "ProceduralGrassPlugin"

		});
	}
}
