// Copyright (c) swaroop. All rights reserved.


#include "ComputeShaderSubsystem.h"

void UComputeShaderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ComputeScene = FSceneViewExtensions::NewExtension<FComputeSceneViewExtension>();
	
}

void UComputeShaderSubsystem::Deinitialize()
{
	Super::Deinitialize();

	ComputeScene.Reset();
	ComputeScene = nullptr;
}
