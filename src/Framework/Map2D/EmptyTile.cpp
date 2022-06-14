#include "EmptyTile.h"

namespace CasaEngine
{
	void EmptyTile::Update(const GameTime& gameTime_)
	{
		//do nothing
	}

	void EmptyTile::Draw(float x, float y, float z)
	{
		//do nothing
	}

	void EmptyTile::Draw(float x, float y, float z, const Rectangle& uvOffset)
	{
		//do nothing
	}

	TileData* EmptyTile::GetTileData()
	{
		return nullptr;
	}
}
