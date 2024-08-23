/*
#include "TileActor.h"
// #include "DrawDebugHelpers.h"


ATileActor::ATileActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATileActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATileActor::GenerateTiles()
{
	if (_tiles.Num() != 0)
		_tiles.Empty();

	_tiles.Empty(FMath::Square(_tileCount));
	
	UE_LOG(LogTemp, Warning, TEXT("they asked me to generate tiles huhuhuhu"));

	int32 _layerIndex = 0;
	int32 _halfTileCount = 1;
	int32 _lastTileIndex = GetLastIndexInLayer(0); // to see when to increment layer

	for (int32 i = 0; i < FMath::Square(_tileCount); i++)
	{
		if (i == _lastTileIndex)
		{
			++_layerIndex;
			++_halfTileCount;
			_lastTileIndex = GetLastIndexInLayer(_layerIndex);

			// UE_LOG(LogTemp, Warning, TEXT("_lastTileIndex_ __layerIndex: %d, i: %d, _lastTileIndex: %d"), _layerIndex, i, _lastTileIndex)
		}

		FVector _location = CalculateTilePosition(i, _layerIndex);
		// UE_LOG(LogTemp, Warning, TEXT("tile location: X: %f, Y: %f, Z: %f"), _location.X, _location.Y, _location.Z);
		AddTile(_location, true);
	}

	return;
}


FTileInfo ATileActor::GetTileInfo(int32 _tileIndex)
{
	// implement logik

	return FTileInfo();
}

int32 ATileActor::GetTileCountInLayer(int32 _layerIndex)
{
	if (!_layerIndex)
		return 0;

	return 4 * (2 * _layerIndex - 1);
}

int32 ATileActor::GetFirstIndexInLayer(int32 _layerIndex)
{
	if (!_layerIndex || _layerIndex == 0)
		return 0;

	return GetLastIndexInLayer(_layerIndex - 1) + 1;
}

int32 ATileActor::GetLastIndexInLayer(int32 _layerIndex)
{
	return (4 * FMath::Square(_layerIndex + 1)) - 1;
}

void ATileActor::AddTile(const FVector& _location, bool _drawDebug)
{
	FTile _tile;
	_tile.Location = _location;

	UE_LOG(LogTemp, Warning, TEXT("tile location: X: %f, Y: %f, Z: %f"), _location.X, _location.Y, _location.Z);


	if (_drawDebug)
		DrawDebugLine(GetWorld(), FVector(_location.X, _location.Y, 50), FVector(_location.X, _location.Y, -50),
		              FColor::Red, true, 100, 1, 2);

	_tiles.Add(_tile);
	
}


// FVector ATileActor::CalculateTilePosition(int32 _tileIndex, int32 _layerIndex)
// {
// 	if (_tileIndex == 0)
// 		return FVector(_sizeX / 2, _sizeY / 2, 0);
//
// 	if (GetFirstIndexInLayer(_layerIndex) == _tileIndex)
// 		return FVector((_tiles[GetLastIndexInLayer(_layerIndex - 1)].Location.X + _sizeX), _sizeY / 2, 0);
//
// 	// check _tileIndex is a corner tile, and that we need to turn
// 	FTile _prevTile = _tiles[_tileIndex - 1];
// 	int32 X = _prevTile.Location.X;
// 	int32 Y = _prevTile.Location.Y;
// 	
// 	if (FMath::Abs(_prevTile.Location.X) == FMath::Abs(_prevTile.Location.Y))
// 	{
//
// 		if (X == Y && X > 0) // (100,100,0)
// 			return FVector(X - _sizeX, Y, 0);
//
// 		if (X * -1 == Y && X < 0) // (-100, 100, 0)
// 			return FVector(X, Y - _sizeY, 0);
//
// 		if (X == Y && X < 0) // (-100,-100,0)
// 			return FVector(X + _sizeX, Y, 0);
// 		
// 		if (X == Y * -1 && X > 0) // (100,-100,0)
// 			return FVector(X, Y + _sizeY, 0);
// 	}
// 	else
// 	{
// 		if (X >= 0 && Y >= 0)
// 		{
// 			if (X > Y) // (100,80,0)
// 				return FVector(X, Y + _sizeY, 0);
// 			if (X < Y) // (80,100,0)
// 				return FVector(X - _sizeX, Y, 0);
// 		}
// 		if (X <= 0 && Y >= 0)
// 		{
// 			if (X * -1 < Y) // (-80,1000,0)
// 				return FVector(X - _sizeX, Y, 0);
// 			if (X * -1 > Y)  // (-100,80,0)
// 				return FVector(X, Y - _sizeY, 0);
// 		}
// 		if (X <= 0 && Y <= 0)
// 		{
// 			if (X < Y)
// 				return FVector(X, Y - _sizeY, 0);
// 			if (X > Y)
// 				return FVector(X + _sizeX, Y, 0);
// 		}
// 		if (X >= 0 && Y <= 0)
// 		{
// 			if (X < Y * -1)
// 				return FVector(X + _sizeX, Y, 0);
// 			if (X > Y * -1)
// 				return FVector(X, Y + _sizeY, 0);
// 		}		
// 	}
// 	
// 	
// 	return FVector::ZeroVector;
// }


FVector ATileActor::CalculateTilePosition(int32 _tileIndex, int32 _layerIndex)
{
	// Early return for the first tile
	if (_tileIndex == 0)
		return FVector(_sizeX / 2, _sizeY / 2, 0);

	// Check if this is the first tile in a new layer
	if (GetFirstIndexInLayer(_layerIndex) == _tileIndex)
		return FVector((_tiles[GetLastIndexInLayer(_layerIndex - 1)].Location.X + _sizeX), _sizeY / 2, 0);

	// Get the previous tile's position
	FTile _prevTile = _tiles[_tileIndex - 1];
	int32 X = _prevTile.Location.X;
	int32 Y = _prevTile.Location.Y;

	// Define an enumeration for movement directions
	UENUM()
	enum EDirection
	{
		MoveLeft,
		MoveDown,
		MoveRight,
		MoveUp,
		None
	};

	// Determine the direction to move based on the current position
	EDirection Direction = None;

	// Determine direction based on corners
	if (FMath::Abs(X) == FMath::Abs(Y)) // At a corner or need to turn
	{
		if (X > 0 && Y > 0) Direction = MoveLeft; // Top-right corner
		else if (X < 0 && Y > 0) Direction = MoveDown; // Top-left corner
		else if (X < 0 && Y < 0) Direction = MoveRight; // Bottom-left corner
		else if (X > 0 && Y < 0) Direction = MoveUp; // Bottom-right corner
	}
	else
	{
		// Determine direction based on quadrants
		if (X >= 0 && Y >= 0) // Top-right quadrant
			Direction = (X > Y) ? MoveUp : MoveLeft;
		else if (X <= 0 && Y >= 0) // Top-left quadrant
			Direction = (X * -1 < Y) ? MoveLeft : MoveDown;
		else if (X <= 0 && Y <= 0) // Bottom-left quadrant
			Direction = (X < Y) ? MoveDown : MoveRight;
		else if (X >= 0 && Y <= 0) // Bottom-right quadrant
			Direction = (X < Y * -1) ? MoveRight : MoveUp;
	}

	// Calculate the new position based on the determined direction
	switch (Direction)
	{
	case MoveLeft:
		return FVector(X - _sizeX, Y, 0);
	case MoveDown:
		return FVector(X, Y - _sizeY, 0);
	case MoveRight:
		return FVector(X + _sizeX, Y, 0);
	case MoveUp:
		return FVector(X, Y + _sizeY, 0);
	default:
		return FVector::ZeroVector;
	}
}
*/
