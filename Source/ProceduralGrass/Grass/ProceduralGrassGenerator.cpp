// Copyright (c) swaroop. All rights reserved.


#include "ProceduralGrassGenerator.h"
#include "Engine/StaticMesh.h"
#include "RHICommandList.h"
#include "ShaderParameterUtils.h"
#include "RenderGraphUtils.h"
#include "Logging/LogMacros.h"



DEFINE_LOG_CATEGORY(ProceduralGrass);
DEFINE_LOG_CATEGORY(ProceduralGrassError);
DEFINE_LOG_CATEGORY(ProceduralGrassAlert);


AProceduralGrassGenerator::AProceduralGrassGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(ProceduralGrass, Log, TEXT("Procedural Grass Generator initiated."));
	
}


void AProceduralGrassGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProceduralGrassGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProceduralGrassGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AProceduralGrassGenerator::GenerateGrass()
{
	UE_LOG(ProceduralGrass, Log, TEXT("Starting to generate grass."));

	if (Mesh == nullptr)
	{
		UE_LOG(ProceduralGrassError, Error, TEXT("No Grass Mesh asset found while trying to generate grass."));
		return;
	}

	// set render data
	RenderData = Mesh->GetRenderData();
	if (RenderData == nullptr)
	{
		UE_LOG(ProceduralGrassError, Error, TEXT("RenderData is null")); 
		return;
	}
	
	// TODO: use all LODs
	// TODO: implement render fence (also figure out wtf it is)
	// TODO: figure out if a cpu readback is needed
	const FStaticMeshLODResources* LODResource = &RenderData->LODResources[0];
	if (LODResource == nullptr || !LODResource)
	{
		UE_LOG(ProceduralGrassError, Error, TEXT("LODResource[0] is null"));
		return;
	}

	UE_LOG(ProceduralGrass, Log, TEXT("ENQUEUE_RENDER_COMMAND: Set VertexBuffer and IndexBuffer"));
	// SRV — Shader Resource View — FShaderResourceViewRHIRef 
	// UAV — Unordered Access View — FUnorderedAccessViewRHIRef
	const auto vBuff = LODResource->VertexBuffers.PositionVertexBuffer.VertexBufferRHI;
	const auto iBuff = LODResource->IndexBuffer.IndexBufferRHI;
	
	ENQUEUE_RENDER_COMMAND(Compute1)([vBuff, iBuff](FRHICommandListImmediate& RHICmdList)
	{
		if (!vBuff.IsValid() || !iBuff.IsValid()) return;
		
		FUnorderedAccessViewRHIRef VertexBuffer = RHICmdList.CreateUnorderedAccessView(vBuff, PF_R32_FLOAT);
		FUnorderedAccessViewRHIRef IndexBuffer = RHICmdList.CreateUnorderedAccessView(iBuff, PF_R32_FLOAT);

		// check if UAV buffers are valid
		if (!VertexBuffer.IsValid() || !IndexBuffer.IsValid()) return;
		
	});
}

void AProceduralGrassGenerator::DestroyGrass()
{
}

