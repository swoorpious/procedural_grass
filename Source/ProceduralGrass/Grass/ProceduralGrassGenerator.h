// Copyright (c) swaroop. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticMeshResources.h"

#include "ProceduralGrassGenerator.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(ProceduralGrass, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ProceduralGrassError, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ProceduralGrassAlert, Log, All);


class FStaticMeshRenderData;

UCLASS()
class PROCEDURALGRASS_API AProceduralGrassGenerator : public AActor
{
	GENERATED_BODY()

public:
	AProceduralGrassGenerator();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category="Grass Functions")
	void GenerateGrass();

	UFUNCTION(BlueprintCallable, Category="Grass Functions")
	void DestroyGrass();

#pragma region Mesh Setup
	UPROPERTY(EditAnywhere, Category="")
	TObjectPtr<UStaticMesh> Mesh = nullptr;

	// Unable to find 'class' with name 'FStaticMeshRenderData' [UnrealHeaderTool Error]
	// If you get that error it means that the type can’t be used in blueprints since unreal engine doesn’t handle reflection for that type.
	// https://forums.unrealengine.com/t/how-are-tsharedptr-types-used-in-blueprints/627521/2
 	FStaticMeshRenderData* RenderData = nullptr;
#pragma endregion

private:
	
};
