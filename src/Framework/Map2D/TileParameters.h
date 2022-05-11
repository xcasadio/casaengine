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
		TileType _type;

	protected:
		TileParameters(TileType type);

	private:
		friend class cereal::access;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("type", _type));
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("type", _type));
		}
	};

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

	private:
		friend class cereal::access;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("tile", cereal::base_class<TileParameters>(this)));
			ar(cereal::make_nvp("sprite_id", spriteId));
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("tile", cereal::base_class<TileParameters>(this)));
			ar(cereal::make_nvp("sprite_id", spriteId));
		}
	};

	class CA_EXPORT AnimatedTileParameters : public TileParameters
	{
	public:
		AnimatedTileParameters();
		~AnimatedTileParameters() = default;
		AnimatedTileParameters(const AnimatedTileParameters & rsh) = default;
		AnimatedTileParameters& operator=(const AnimatedTileParameters & rsh) = default;
		AnimatedTileParameters(AnimatedTileParameters && rsh) = default;
		AnimatedTileParameters& operator=(AnimatedTileParameters && rsh) = default;

		std::string animation2DId;

	private:
		friend class cereal::access;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("tile", cereal::base_class<TileParameters>(this)));
			ar(cereal::make_nvp("animation_2d_id", animation2DId));
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("tile", cereal::base_class<TileParameters>(this)));
			ar(cereal::make_nvp("animation_2d_id", animation2DId));
		}
	};

	class CA_EXPORT AutoTileParameters : public TileParameters
	{
	public:
		AutoTileParameters();
		~AutoTileParameters() = default;
		AutoTileParameters(const AutoTileParameters & rsh) = default;
		AutoTileParameters& operator=(const AutoTileParameters & rsh) = default;
		AutoTileParameters(AutoTileParameters && rsh) = default;
		AutoTileParameters& operator=(AutoTileParameters && rsh) = default;

		std::string _autoTileAssetName;

	private:
		friend class cereal::access;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("tile", cereal::base_class<TileParameters>(this)));
			ar(cereal::make_nvp("auto_tile_asset_name", _autoTileAssetName));
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("tile", cereal::base_class<TileParameters>(this)));
			ar(cereal::make_nvp("auto_tile_asset_name", _autoTileAssetName));
		}
	};

	class TiledMapParameters;

	class CA_EXPORT TiledMapLayerParameters
	{
	public:
		std::vector<TileParameters*> tiles;
		float zOffset;

	private:
		friend class cereal::access;

		template <class Archive>
		void save(Archive& ar) const
		{
			std::vector<TileParameters> tiles2;
			tiles2.resize(tiles.size());
			std::transform(tiles.begin(), tiles.end(), tiles2.begin(), [](TileParameters* x) { return *x; });
			ar(CEREAL_NVP(tiles2));
			ar(cereal::make_nvp("z_offset", zOffset));
		}

		template <class Archive>
		void load(Archive& ar)
		{
			//ar(CEREAL_NVP(tiles));
			ar(cereal::make_nvp("z_offset", zOffset));
		}
	};

	class CA_EXPORT TiledMapParameters
	{
	public:
		Coordinates coordinates;
		Vector2I mapSize;
		Vector2I tileSize;
		std::vector<TiledMapLayerParameters> layers;

	private:
		friend class cereal::access;

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(CEREAL_NVP(coordinates));
			ar(cereal::make_nvp("map_size", mapSize));
			ar(cereal::make_nvp("tile_size", tileSize));
			ar(CEREAL_NVP(layers));
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(CEREAL_NVP(coordinates));
			ar(cereal::make_nvp("map_size", mapSize));
			ar(cereal::make_nvp("tile_size", tileSize));
			ar(CEREAL_NVP(layers));
		}
	};

	class CA_EXPORT TiledMapCreator
	{
	public:
		static void Create(TiledMapParameters& tiledMapParameters, World& world);
		static ITile* CreateTile(TileParameters& tileParameters, TiledMapLayerParameters* layer, TiledMapParameters* map);
	};
}
