#pragma once

#include <vector>

#include "CA_Export.h"
#include "Maths/Vector2.h"

namespace CasaEngine
{
	enum class TileType : int
	{
		Static = 0,
		Animated,
		Auto
	};

	enum class TileCollisionType : int
	{
		None = 0,
		Blocked,
		NoContactResponse
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

		int id;
		TileType type;
		TileCollisionType collisionType;
		bool isBreakable { false };

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

	//class CA_EXPORT AutoTileData : public TileData
	//{
	//public:
	//	AutoTileData();
	//	~AutoTileData() = default;
	//	AutoTileData(const AutoTileData& rsh) = default;
	//	AutoTileData& operator=(const AutoTileData& rsh) = default;
	//	AutoTileData(AutoTileData&& rsh) = default;
	//	AutoTileData& operator=(AutoTileData&& rsh) = default;
	//
	//	std::string autoTileAssetName;
	//};

	////////////////////////////////////////

	class CA_EXPORT TileSetData
	{
	public:
		TileSetData() = default;
		~TileSetData() = default;
		TileSetData(const TileSetData& rsh) = default;
		TileSetData& operator=(const TileSetData& rsh) = default;
		TileSetData(TileSetData&& rsh) = default;
		TileSetData& operator=(TileSetData&& rsh) = default;

		TileData* GetTileById(int id);

		std::string spriteSheetFileName;
		Vector2I tileSize;
		std::vector<TileData*> tiles;
	};

	////////////////////////////////////////

	class CA_EXPORT AutoTileTileSetData
	{
	public:
		AutoTileTileSetData() = default;
		~AutoTileTileSetData() = default;
		AutoTileTileSetData(const AutoTileTileSetData& rsh) = default;
		AutoTileTileSetData& operator=(const AutoTileTileSetData& rsh) = default;
		AutoTileTileSetData(AutoTileTileSetData&& rsh) = default;
		AutoTileTileSetData& operator=(AutoTileTileSetData&& rsh) = default;

		TileData* GetTileById(const int id);

		int id;
		std::vector<TileData*> tiles;
	};

	////////////////////////////////////////

	class CA_EXPORT AutoTileSetData
	{
		public:
			AutoTileSetData() = default;
			~AutoTileSetData() = default;
			AutoTileSetData(const AutoTileSetData& rsh) = default;
			AutoTileSetData& operator=(const AutoTileSetData& rsh) = default;
			AutoTileSetData(AutoTileSetData&& rsh) = default;
			AutoTileSetData& operator=(AutoTileSetData&& rsh) = default;

			AutoTileTileSetData *GetTileSetById(const int id);

			std::string spriteSheetFileName;
			Vector2I tileSize;
			std::vector<AutoTileTileSetData> sets;
	};
}
