// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../FastNoiseLite.h"
#include "RHI.h"
#include "RHICommandList.h"



#include "GrassActor.generated.h"

class UHierarchicalInstancedStaticMeshComponent;

UENUM(BlueprintType)
enum class ENoiseType : uint8 {
    Simplex UMETA(DisplayName = "Simplex"),
    Cellular UMETA(DisplayName = "Cellular"),
    Perlin UMETA(DisplayName = "Perlin"),
};

DECLARE_LOG_CATEGORY_EXTERN(GrassSpawnTransform, Log, All);

UCLASS()
class PROCEDURALGRASS_API AGrassActor : public AActor
{
    GENERATED_BODY()

public:
    AGrassActor();

#pragma region Material
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grass|Material")
    UMaterialInstance* MaterialInstance;
#pragma endregion
    
#pragma region Noise
    UPROPERTY(EditAnywhere, Category = "Grass|Noise")
    ENoiseType NoiseType;

    UPROPERTY(EditAnywhere, Category = "Grass|Noise")
    int32 Seed = 0;

    UPROPERTY(EditAnywhere, Category = "Grass|Noise")
    double Frequency = 0.001f;
#pragma endregion

#pragma region Tile Properties
    UPROPERTY(EditAnywhere, Category = "Grass|Tile Properties")
    float Size = 8; // 8m

    UPROPERTY(EditAnywhere, Category = "Grass|Tile Properties")
    float Density = 128;
#pragma endregion

#pragma region Grass Transforms
    UPROPERTY(EditAnywhere, Category = "Grass|Transform")
    float TranslationRandomness = 0.0f; // +-TranslationRandomness

    UPROPERTY(EditAnywhere, Category = "Grass|Transform")
    FVector ScaleAdjustment = FVector(1.0f, 1.0f, 1.0f); // vertical scale

    UPROPERTY(EditAnywhere, Category = "Grass|Transform")
    float MinHeight = 0.2f; // vertical scale - 0.2f

    UPROPERTY(EditAnywhere, Category = "Grass|Transform")
    float MaxHeight = 0.2f; // vertical scale + 0.2f

    UPROPERTY(EditAnywhere, Category = "Grass|Transform|Rotation")
    float RotationRandomness = 0.0f; // +-RotationRandomness

    UPROPERTY(EditAnywhere, Category = "Grass|Transform|Rotation")
    FVector RotationAdjustment = FVector::ZeroVector;
#pragma endregion

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void OnConstruction(const FTransform& Transform) override;

    FastNoiseLite Noise;
    FVector GetWorldCoordinates(int32 X, int32 Y) const;

    UFUNCTION(BlueprintCallable, Category="Grass Functions")
    void GenerateGrass();

    UFUNCTION(BlueprintCallable, Category="Grass Functions")
    void DestroyGrass();

private:
    FVector GetLocationAtPoint(const FVector2D& AbsoluteLocation, const FVector& WorldLocation, float NoiseValue) const;
    FRotator GetRotationAtPoint(const FVector2D& AbsoluteLocation, float NoiseValue) const;
    FVector GetScaleAtPoint(const FVector2D& AbsoluteLocation, float NoiseValue) const;

    void InitializeNoise();
    void InitializeBuffers();
    void UpdateInstanceData(FRHICommandListImmediate& RHICmdList);
    void RenderInstances(FRHICommandListImmediate& RHICmdList);
    
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USceneComponent> SceneComponent;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UHierarchicalInstancedStaticMeshComponent> InstancedStaticMeshComponent;
};
