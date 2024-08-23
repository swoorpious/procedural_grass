#include "GrassActor.h"

#include "ToolContextInterfaces.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Async/Async.h"

#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "ShaderParameterUtils.h"
#include "RHIStaticStates.h"
#include "RenderCommandFence.h"
#include "RenderResource.h"
#include "Runtime/RenderCore/Public/RenderGraphUtils.h"
#include "RHIDefinitions.h"
#include "ShaderParameterMacros.h"
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
#include "PipelineStateCache.h"
#include "RenderingThread.h"

DEFINE_LOG_CATEGORY(GrassSpawnTransform);


AGrassActor::AGrassActor()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    RootComponent = SceneComponent;

    InstancedStaticMeshComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
    InstancedStaticMeshComponent->SetupAttachment(RootComponent);
}

void AGrassActor::InitializeBuffers()
{
}

void AGrassActor::UpdateInstanceData(FRHICommandListImmediate& RHICmdList)
{
}

void AGrassActor::RenderInstances(FRHICommandListImmediate& RHICmdList)
{
}


void AGrassActor::BeginPlay()
{
    Super::BeginPlay();
}

void AGrassActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGrassActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
}


FVector AGrassActor::GetWorldCoordinates(int32 X, int32 Y) const
{
    FVector Location = this->GetActorLocation();
    return FVector(Location.X + X, Location.Y + Y, 0);
}

void AGrassActor::GenerateGrass()
{
    if (InstancedStaticMeshComponent->GetInstanceCount() != 0)
        DestroyGrass();
    
    InitializeNoise();

    Async(EAsyncExecution::ThreadPool, [this]()
    {
        TArray<FTransform> InstanceTransforms;
        
        for (int i = 0; i <= Density; i++)
        {
            for (int j = 0; j <= Density; j++)
            {
                float x = i / Density;
                float y = j / Density;

                FVector WorldLocation = GetWorldCoordinates(x, y);
                FVector2D AbsoluteLocation(x, y);
                
                float NoiseValue = Noise.GetNoise(AbsoluteLocation.X, AbsoluteLocation.Y);
                
                FVector GrassLocation = GetLocationAtPoint(AbsoluteLocation, WorldLocation, NoiseValue);
                FRotator GrassRotation = GetRotationAtPoint(AbsoluteLocation, NoiseValue);
                FVector GrassScale = GetScaleAtPoint(AbsoluteLocation, NoiseValue);

                FTransform GrassTransform(GrassRotation, GrassLocation, GrassScale);
                // GrassTransform.SetLocation(GrassLocation);
                // GrassTransform.SetRotation(GrassRotation.Quaternion());
                
                InstanceTransforms.Add(GrassTransform);
            }
        }

        AsyncTask(ENamedThreads::GameThread, [this, InstanceTransforms]()
        {
            for (const FTransform& Transform : InstanceTransforms)
            {
                InstancedStaticMeshComponent->AddInstance(Transform);
            }
        });
    });
}

void AGrassActor::DestroyGrass()
{
    InstancedStaticMeshComponent->ClearInstances();
}

FVector AGrassActor::GetLocationAtPoint(const FVector2D& AbsoluteLocation, const FVector& WorldLocation, float NoiseValue) const
{
    FVector RandomOffset(FMath::RandRange(-TranslationRandomness, TranslationRandomness), FMath::RandRange(-TranslationRandomness, TranslationRandomness), 0);

    auto s = AbsoluteLocation.X * Size * 100;
    FVector Location(s - Size * 50 + RandomOffset.X, AbsoluteLocation.Y * Size * 100 - Size * 50 + RandomOffset.Y, 0);
    
    return Location;
}

FRotator AGrassActor::GetRotationAtPoint(const FVector2D& AbsoluteLocation, float NoiseValue) const
{
    return FRotator(RotationAdjustment.X + FMath::RandRange(-RotationRandomness, RotationRandomness), RotationAdjustment.Y + FMath::RandRange(-RotationRandomness, RotationRandomness), RotationAdjustment.Z + FMath::RandRange(-RotationRandomness, RotationRandomness));
}

FVector AGrassActor::GetScaleAtPoint(const FVector2D& AbsoluteLocation, float NoiseValue) const
{
    return FVector(ScaleAdjustment.X, ScaleAdjustment.Y, ScaleAdjustment.Z + NoiseValue * MaxHeight);
}


void AGrassActor::InitializeNoise()
{
    switch (NoiseType)
    {
    case ENoiseType::Perlin:
        Noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        break;
    case ENoiseType::Simplex:
        Noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        break;
    case ENoiseType::Cellular:
        Noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
        break;
    }

    Noise.SetSeed(Seed);
    Noise.SetFrequency(Frequency);
}
