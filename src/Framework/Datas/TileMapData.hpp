#pragma once

#include <vector>

#include  "TileSetData.hpp"
#include  "Entities/Components/Coordinates.hpp"
#include  "Maths/Vector2.hpp"
#include  "Maths/Vector3.hpp"
#include  "World/World.hpp"

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
