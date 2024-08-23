#pragma once
/*
// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreMinimal.h"
// #include "GameFramework/Actor.h"
#include "TileActor.generated.h"

USTRUCT()
struct FTile
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FVector Location;

	FTile()
	{
		
	}
};

USTRUCT()
struct FTileInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int32 X;
	
	UPROPERTY()
	int32 Y;

	UPROPERTY()
	int32 Z;

	FTileInfo()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}
	FTileInfo(int32 x, int32 y, int32 z)
	{
		X = x;
		Y = y;
		Z = z;
	}
	FTileInfo(const FVector* _loc)
	{
		X = _loc->X;
		Y = _loc->Y;
		Z = _loc->Z;
	}
	
}; 


UCLASS()
class PROCEDURALGRASS_API ATileActor : public AActor
{

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	ATileActor();

	// number of tiles in X and Y directions
	UPROPERTY(EditAnywhere, Category="TileProperties")
	int32 _tileCount = 8; // total tiles = 8 * 8

	// values in meter
	UPROPERTY(EditAnywhere, Category="TileProperties")
	int32 _sizeX = 32; // 32m
	UPROPERTY(EditAnywhere, Category="TileProperties")
	int32 _sizeY = 32; // 32m
	
	UFUNCTION(BlueprintCallable, Exec, Category="TileUtils")
	void GenerateTiles();
	
protected:

private:
	TArray<FTile> _tiles;

	FTileInfo GetTileInfo(int32 _tileIndex);
	int32 GetTileCountInLayer(int32 _layerIndex);
	int32 GetFirstIndexInLayer(int32 _layerIndex);
	int32 GetLastIndexInLayer(int32 _layerIndex);
	FVector CalculateTilePosition(int32 _tileIndex, int32 _layerIndex);

	void AddTile(const FVector& _location, bool _drawDebug);
	
	GENERATED_BODY()


	
};
*/
