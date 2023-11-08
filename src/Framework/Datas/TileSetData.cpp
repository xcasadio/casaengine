#include  "TileSetData.hpp"

namespace CasaEngine
{
	TileData* TileSetData::GetTileById(int id)
	{
		for (auto* tile : tiles)
		{
			if (tile->id == id)
			{
				return tile;
			}
		}
		return nullptr;
	}

	TileData* AutoTileTileSetData::GetTileById(const int id)
	{
		for (auto* tile : tiles)
		{
			if (tile->id == id)
			{
				return tile;
			}
		}
		return nullptr;
	}

	AutoTileTileSetData* AutoTileSetData::GetTileSetById(const int id)
	{
		for (auto& set : sets)
		{
			if (set.id == id)
			{
				return &set;
			}
		}

		return nullptr;
	}
}
