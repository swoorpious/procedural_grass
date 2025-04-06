// Copyright (c) swaroop. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SceneViewExtension.h"
#include "RenderGraphUtils.h"
// #include "PostProcess/PostProcessing.h"
// #include "ComputeSceneViewExtension.generated.h"

/**
 * 
 */

class PROCEDURALGRASSPLUGIN_API FComputeSceneViewExtension : public FSceneViewExtensionBase
{
public:
	FComputeSceneViewExtension(const FAutoRegister& AutoRegister);
	virtual ~FComputeSceneViewExtension() override;

	virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;
	virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;

private:
	FVector CameraPosition;
	FMatrix CameraViewMatrix;
	FMatrix CameraProjectionMatrix;
};
