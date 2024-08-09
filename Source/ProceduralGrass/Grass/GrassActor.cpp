#include "GrassActor.h"

#include "ToolContextInterfaces.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Async/Async.h"

DEFINE_LOG_CATEGORY(GrassSpawnTransform);


AGrassActor::AGrassActor()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    RootComponent = SceneComponent;

    InstancedStaticMeshComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
    InstancedStaticMeshComponent->SetupAttachment(RootComponent);
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
                
                FVector GrassLocation = GetLocationAtPoint(AbsoluteLocation, WorldLocation);
                FRotator GrassRotation = GetRotationAtPoint(AbsoluteLocation);
                FVector GrassScale = GetScaleAtPoint(AbsoluteLocation);

                FTransform GrassTransform(GrassRotation, GrassLocation, GrassScale);
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

FVector AGrassActor::GetLocationAtPoint(const FVector2D& AbsoluteLocation, const FVector& WorldLocation) const
{

    // float NoiseValue = Noise.GetNoise(AbsoluteLocation.X, AbsoluteLocation.Y);
    FVector RandomOffset(FMath::RandRange(-TranslationRandomness, TranslationRandomness), FMath::RandRange(-TranslationRandomness, TranslationRandomness), 0);

    auto s = AbsoluteLocation.X * Size * 100;
    FVector Location(s - Size * 50 + RandomOffset.X, AbsoluteLocation.Y * Size * 100 - Size * 50 + RandomOffset.Y, 0);
    
    return Location;
}

FRotator AGrassActor::GetRotationAtPoint(const FVector2D& AbsoluteLocation) const
{
    float NoiseValue = Noise.GetNoise(AbsoluteLocation.X, AbsoluteLocation.Y);
    return FRotator(0, FMath::RandRange(-RotationRandomness, RotationRandomness), 0);
}

FVector AGrassActor::GetScaleAtPoint(const FVector2D& AbsoluteLocation) const
{
    float NoiseValue = Noise.GetNoise(AbsoluteLocation.X, AbsoluteLocation.Y);
    return FVector(1.0f, 0.8f, Height + FMath::Clamp(NoiseValue, MinHeight, MaxHeight));
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
