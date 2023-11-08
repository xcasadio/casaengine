#include  "TileSetData.hpp"

namespace CasaEngine
{
	TileData::TileData(TileType type) :
		id(0),
		type(type),
		collisionType(TileCollisionType::None)
	{
	}

	StaticTileData::StaticTileData() : TileData(TileType::Static) { }

	AnimatedTileData::AnimatedTileData() : TileData(TileType::Animated) { }

	//AutoTileData::AutoTileData() : TileData(TileType::Auto) { }
}
