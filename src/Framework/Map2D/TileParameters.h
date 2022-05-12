#pragma once

#include <vector>

#include "Tile.h"
#include "Maths/Vector2.h"
#include "Maths/Vector3.h"

namespace CasaEngine
{
	enum class TileType : int
	{
		Static = 0,
		Animated,
		Auto
	};

	class CA_EXPORT TileParameters
	{
	public:
		TileParameters() = default;
		~TileParameters() = default;
		TileParameters(const TileParameters& rsh) = default;
		TileParameters& operator=(const TileParameters& rsh) = default;
		TileParameters(TileParameters&& rsh) = default;
		TileParameters& operator=(TileParameters&& rsh) = default;

		float x;
		float y;
		TileType type;

	protected:
		TileParameters(TileType type);
	};

	////////////////////////////////////////

	class CA_EXPORT StaticTileParameters : public TileParameters
	{
	public:
		StaticTileParameters();
		~StaticTileParameters() = default;
		StaticTileParameters(const StaticTileParameters& rsh) = default;
		StaticTileParameters& operator=(const StaticTileParameters& rsh) = default;
		StaticTileParameters(StaticTileParameters&& rsh) = default;
		StaticTileParameters& operator=(StaticTileParameters&& rsh) = default;

		std::string spriteId;
	};

	////////////////////////////////////////
	
	class CA_EXPORT AnimatedTileParameters : public TileParameters
	{
	public:
		AnimatedTileParameters();
		~AnimatedTileParameters() = default;
		AnimatedTileParameters(const AnimatedTileParameters& rsh) = default;
		AnimatedTileParameters& operator=(const AnimatedTileParameters& rsh) = default;
		AnimatedTileParameters(AnimatedTileParameters&& rsh) = default;
		AnimatedTileParameters& operator=(AnimatedTileParameters&& rsh) = default;

		std::string animation2DId;
	};

	////////////////////////////////////////

	class CA_EXPORT AutoTileParameters : public TileParameters
	{
	public:
		AutoTileParameters();
		~AutoTileParameters() = default;
		AutoTileParameters(const AutoTileParameters& rsh) = default;
		AutoTileParameters& operator=(const AutoTileParameters& rsh) = default;
		AutoTileParameters(AutoTileParameters&& rsh) = default;
		AutoTileParameters& operator=(AutoTileParameters&& rsh) = default;

		std::string autoTileAssetName;
	};

	////////////////////////////////////////

	class TiledMapParameters;

	class CA_EXPORT TiledMapLayerParameters
	{
	public:
		std::vector<TileParameters*> tiles;
		float zOffset;
	};

	////////////////////////////////////////

	class CA_EXPORT TiledMapParameters
	{
	public:
		Coordinates coordinates;
		Vector2I mapSize;
		Vector2I tileSize;
		std::vector<TiledMapLayerParameters> layers;
	};

	////////////////////////////////////////

	class CA_EXPORT TiledMapCreator
	{
	public:
		static void Create(TiledMapParameters& tiledMapParameters, World& world);
		static ITile* CreateTile(TileParameters& tileParameters, TiledMapLayerParameters* layer, TiledMapParameters* map);
	};
}
