// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralGrassPlugin.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FProceduralGrassPluginModule"

void FProceduralGrassPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	const FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("ProceduralGrassPlugin"))->GetBaseDir(), TEXT("Shaders"));
	// Requires RenderCore
	if(!AllShaderSourceDirectoryMappings().Contains(TEXT("/PGShaders"))) {
		AddShaderSourceDirectoryMapping(TEXT("/PGShaders"), PluginShaderDir);
	}
}

void FProceduralGrassPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FProceduralGrassPluginModule, ProceduralGrassPlugin)