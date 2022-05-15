#pragma once

#include <vector>

#include "Tile.h"
#include "Entities/Components/Coordinates.h"
#include "Maths/Vector2.h"
#include "Maths/Vector3.h"
#include "World/World.h"

namespace CasaEngine
{
	enum class TileType : int
	{
		Static = 0,
		Animated,
		Auto
	};

	////////////////////////////////////////

	class CA_EXPORT TileData
	{
	public:
		TileData() = default;
		~TileData() = default;
		TileData(const TileData& rsh) = default;
		TileData& operator=(const TileData& rsh) = default;
		TileData(TileData&& rsh) = default;
		TileData& operator=(TileData&& rsh) = default;

		float x;
		float y;
		TileType type;

	protected:
		TileData(TileType type);
	};

	////////////////////////////////////////

	class CA_EXPORT StaticTileData : public TileData
	{
	public:
		StaticTileData();
		~StaticTileData() = default;
		StaticTileData(const StaticTileData& rsh) = default;
		StaticTileData& operator=(const StaticTileData& rsh) = default;
		StaticTileData(StaticTileData&& rsh) = default;
		StaticTileData& operator=(StaticTileData&& rsh) = default;

		std::string spriteId;
	};

	////////////////////////////////////////
	
	class CA_EXPORT AnimatedTileData : public TileData
	{
	public:
		AnimatedTileData();
		~AnimatedTileData() = default;
		AnimatedTileData(const AnimatedTileData& rsh) = default;
		AnimatedTileData& operator=(const AnimatedTileData& rsh) = default;
		AnimatedTileData(AnimatedTileData&& rsh) = default;
		AnimatedTileData& operator=(AnimatedTileData&& rsh) = default;

		std::string animation2DId;
	};

	////////////////////////////////////////

	class CA_EXPORT AutoTileData : public TileData
	{
	public:
		AutoTileData();
		~AutoTileData() = default;
		AutoTileData(const AutoTileData& rsh) = default;
		AutoTileData& operator=(const AutoTileData& rsh) = default;
		AutoTileData(AutoTileData&& rsh) = default;
		AutoTileData& operator=(AutoTileData&& rsh) = default;

		std::string autoTileAssetName;
	};

	////////////////////////////////////////

	class TiledMapData;

	class CA_EXPORT TiledMapLayerData
	{
	public:
		std::vector<TileData*> tiles;
		float zOffset;
	};

	////////////////////////////////////////

	class CA_EXPORT TiledMapData
	{
	public:
		Coordinates coordinates;
		Vector2I mapSize;
		Vector2I tileSize;
		std::vector<TiledMapLayerData> layers;
		std::string spriteSheetFileName;
	};

	////////////////////////////////////////

	class CA_EXPORT TiledMapCreator
	{
	public:
		static void Create(TiledMapData& tiledMapParameters, World& world);
		static ITile* CreateTile(TileData& tileParameters, TiledMapLayerData* layer, TiledMapData* map);
	};
}
