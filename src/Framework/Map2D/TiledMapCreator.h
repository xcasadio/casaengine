#pragma once

#include "Tile.h"
#include "Datas/TileSetData.h"
#include "Datas/TileMapData.h"
#include "World/World.h"

namespace CasaEngine
{
	class CA_EXPORT TiledMapCreator
	{
	public:
		static void LoadMapFromFile(std::string fileName, World& world);
		static void Create(std::string prefixName, AutoTileSetData& autoTileSetData, TileSetData& tileSetData, TiledMapData& tiledMapData, World& world);
		static ITile* CreateTile(TileData& tileData);
		static ITile* CreateTile(const AutoTileTileSetData& autoTileTileSetData, const TileSetData& tileSetData, TiledMapLayerData* layer, const TiledMapData* map, int x, int y);
	};
}
