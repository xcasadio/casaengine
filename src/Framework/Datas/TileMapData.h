#pragma once

#include <vector>

#include "TileSetData.h"
#include "Entities/Components/Coordinates.h"
#include "Maths/Vector2.h"
#include "Maths/Vector3.h"
#include "World/World.h"

namespace CasaEngine
{
	class CA_EXPORT TiledMapLayerData
	{
	public:
		std::vector<int> tilesId;
		float zOffset;
		TileType type;
	};

	////////////////////////////////////////

	class CA_EXPORT TiledMapData
	{
	public:
		Coordinates coordinates;
		Vector2I mapSize;
		std::vector<TiledMapLayerData> layers;
		std::string tileSetFileName;
		std::string autoTileSetFileName;
	};
}
