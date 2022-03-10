#include"Grid.h"
#include"Tile.h"
#include"Tower.h"
#include"Enemy.h"
#include<algorithm>
Grid::Grid(Game* game)
	:Actor(game)
	,mSelectTile(nullptr)
{
	mTiles.resize(NumRows);
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].resize(NumCols);
	}

	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j] = new Tile(GetGame());
			mTiles[i][j]->SetPosition(Vector2(TileSize / 2.0f + j * TileSize, StartY + i * TileSize));
		}
	}
}

void Grid::ProcessClick(int x, int y)
{
}

bool Grid::FindPath(Tile* start, Tile goal)
{
	return false;
}

void Grid::BuildTower()
{
}

Tile* Grid::GetStartTile()
{
	return nullptr;
}

Tile* Grid::GetEndTile()
{
	return nullptr;
}

void Grid::UpdateActor(float deltaTime)
{
}

void Grid::SelectTile(size_t row, size_t col)
{
}

void Grid::UpdatePathTiles(Tile* Start)
{
}
