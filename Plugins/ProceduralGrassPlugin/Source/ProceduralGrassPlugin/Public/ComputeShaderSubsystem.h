// Copyright (c) swaroop. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "Rendering/ComputeSceneViewExtension.h"
#include "ComputeShaderSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALGRASSPLUGIN_API UComputeShaderSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

	TSharedPtr<FComputeSceneViewExtension, ESPMode::ThreadSafe> ComputeScene;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
