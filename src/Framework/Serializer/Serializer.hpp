#pragma once

#include  "Exceptions.hpp"
#include  "Maths/Vector2.hpp"
#include  "Maths/Vector3.hpp"
#include  "Maths/Vector4.hpp"
#include  "Maths/Rectangle.hpp"
#include  "Maths/Quaternion.hpp"
#include <Assets/Assetable.hpp>
#include <Physics/Collision.hpp>
#include <Datas/SpriteData.hpp>
#include <Datas/TileSetData.hpp>
#include <Datas/TileMapData.hpp>
#include  "Datas/Animation2DData.hpp"
#include  "Datas/AnimationData.hpp"
#include  "Datas/FrameData.hpp"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace CasaEngine
{
#define DECLARE_SERIALIZABLE(name) \
	void to_json(nlohmann::json& j, const name & t);\
	void from_json(const nlohmann::json& j, name & t);

#define JSON_TO(v1) j[#v1] = t.v1;
#define JSON_FROM(v1) j.at(#v1).get_to(t.v1);
#define JSON_TO_NAMED(v1, v2) j[#v1] = t.v2;
#define JSON_FROM_NAMED(v1, v2) j.at(#v1).get_to(t.v2);

	void to_json(nlohmann::json& j, TileData* t);
	DECLARE_SERIALIZABLE(TileData)
		DECLARE_SERIALIZABLE(StaticTileData)
		DECLARE_SERIALIZABLE(AnimatedTileData)
		//DECLARE_SERIALIZABLE(AutoTileData)
		DECLARE_SERIALIZABLE(Animation2DData)

		template <class T>
	void to_json(nlohmann::json& j, const std::vector<T>& t, const char* name)
	{
		j.push_back(json::object_t::value_type(name, t));
	}

	//template <class T>
	//void to_json(nlohmann::json& j, const std::vector<T>& t)
	//{
	//	j.push_back(json::array_t::value_type(t));
	//}

	template <class T>
	void from_json(const nlohmann::json& j, std::vector<T>& t)
	{
		for (auto it = j.begin();
			it != j.end();
			++it)
		{
			T obj;
			from_json(*it, obj);
			t.push_back(obj);
		}
	}

	//////////////////////////////////////////////////////////////

	template <class T>
	void to_json(nlohmann::json& j, const CVector2<T>& t)
	{
		JSON_TO(x)
			JSON_TO(y)
	}

	template <class T>
	void from_json(const nlohmann::json& j, CVector2<T>& t)
	{
		JSON_FROM(x)
			JSON_FROM(y)
	}

	//////////////////////////////////////////////////////////////

	template <class T>
	void to_json(nlohmann::json& j, const CVector3<T>& t)
	{
		JSON_TO(x)
			JSON_TO(y)
			JSON_TO(z)
	}

	template <class T>
	void from_json(const nlohmann::json& j, CVector3<T>& t)
	{
		JSON_FROM(x)
			JSON_FROM(y)
			JSON_FROM(z)
	}

	//////////////////////////////////////////////////////////////

	template <class T>
	void to_json(nlohmann::json& j, const CVector4<T>& t)
	{
		JSON_TO(x)
			JSON_TO(y)
			JSON_TO(z)
			JSON_TO(w)
	}

	template <class T>
	void from_json(const nlohmann::json& j, CVector4<T>& t)
	{
		JSON_FROM(x)
			JSON_FROM(y)
			JSON_FROM(z)
			JSON_FROM(w)
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const Quaternion& t)
	{
		JSON_TO(x)
			JSON_TO(y)
			JSON_TO(z)
			JSON_TO(w)
	}

	inline void from_json(const nlohmann::json& j, Quaternion& t)
	{
		JSON_FROM(x)
			JSON_FROM(y)
			JSON_FROM(z)
			JSON_FROM(w)
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const IShape& t)
	{
		JSON_TO_NAMED(shape_type, Type())
	}

	inline void from_json(const nlohmann::json& j, IShape& t)
	{
		//do nothing
	}

	//////////////////////////////////////////////////////////////

	template <class T>
	void to_json(nlohmann::json& j, const CRectangle<T>& t)
	{
		to_json(j, static_cast<const IShape&>(t));
		JSON_TO(x)
			JSON_TO(y)
			JSON_TO(w)
			JSON_TO(h)
	}

	template <class T>
	void from_json(const nlohmann::json& j, CRectangle<T>& t)
	{
		from_json(j, static_cast<IShape&>(t));
		JSON_FROM(x)
			JSON_FROM(y)
			JSON_FROM(w)
			JSON_FROM(h)
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const IAssetable& t)
	{
		JSON_TO_NAMED(asset_name, GetName())
	}

	inline void from_json(const nlohmann::json& j, IAssetable& t)
	{
		t.SetName(j.at("asset_name").get<std::string>());
	}

	//////////////////////////////////////////////////////////////

	//NLOHMANN_JSON_SERIALIZE_ENUM(CollisionHitType, {
	//	{Unknown, "unknown"},
	//	{Attack, "attack"},
	//	{Defense, "defense"}
	//	})

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, IShape* shape)
	{
		switch (shape->Type())
		{
		case ShapeType::RECTANGLE:
			to_json(j, *dynamic_cast<Rectangle*>(shape));
			return;
		case ShapeType::BOX: break;
		case ShapeType::SPHERE: break;
		case ShapeType::CAPSULE: break;
		case ShapeType::CIRCLE2D: break;
		case ShapeType::POLYGON: break;
		}

		throw std::logic_error("to_json() IShape ShapeType not supported");
	}

	inline void from_json(const nlohmann::json& j, IShape** shape)
	{
		*shape = nullptr;
		//todo remove the level "shape"
		auto shapeType = (ShapeType)j.at("shape_type").get<int>();

		switch (shapeType)
		{
		case ShapeType::BOX: break;
		case ShapeType::SPHERE: break;
		case ShapeType::CAPSULE: break;
		case ShapeType::RECTANGLE:
		{
			auto rectangle = new Rectangle();
			from_json(j, *rectangle);
			*shape = rectangle;
			return;
		}
		case ShapeType::CIRCLE2D: break;
		case ShapeType::POLYGON: break;
		}

		throw std::logic_error("from_json() IShape ShapeType not supported");
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const Collision& t)
	{
		to_json(j, t.GetShape());
		JSON_TO_NAMED(collision_type, GetType())
	}

	inline void from_json(const nlohmann::json& j, Collision& t)
	{
		t.SetType((CollisionHitType)j.at("collision_type").get<int>());
		IShape* shape;
		from_json(j, &shape);
		t.SetShape(shape);
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const SpriteData& t)
	{
		to_json(j, static_cast<const IAssetable&>(t));
		JSON_TO_NAMED(sprite_sheet, GetAssetFileName())
			to_json(j["location"], t.GetPositionInTexture());
		to_json(j["hotspot"], t.GetOrigin());
		to_json(j, t._collisionShapes, "collisions");
	}

	inline void from_json(const nlohmann::json& j, SpriteData& t)
	{
		Rectangle r;
		Vector2I v2;
		t.SetAssetFileName(j.at("sprite_sheet").get<std::string>());
		from_json(j.at("location"), r);
		t.SetPositionInTexture(r);
		from_json(j.at("hotspot"), v2);
		t.SetOrigin(v2);
		from_json(j.at("collisions"), t._collisionShapes);
		from_json(j, static_cast<IAssetable&>(t));
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const FrameData& t)
	{
		to_json(j, static_cast<const IAssetable&>(t));
		JSON_TO_NAMED(duration, _duration)
			JSON_TO_NAMED(sprite_id, _spriteId)
	}

	inline void from_json(const nlohmann::json& j, FrameData& t)
	{
		j.at("duration").get_to(t._duration);
		j.at("sprite_id").get_to(t._spriteId);
		from_json(j, static_cast<IAssetable&>(t));
	}

	//////////////////////////////////////////////////////////////

	NLOHMANN_JSON_SERIALIZE_ENUM(AnimationType, { {Once, "once"}, {PingPong, "pingPong"}, {Loop, "loop"} })

		inline void to_json(nlohmann::json& j, const AnimationData& t)
	{
		JSON_TO_NAMED(animation_type, _animationType)
			to_json(j, static_cast<const IAssetable&>(t));
	}

	inline void from_json(const nlohmann::json& j, AnimationData& t)
	{
		JSON_FROM_NAMED(animation_type, _animationType)
			from_json(j, static_cast<IAssetable&>(t));
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const Animation2DData& t)
	{
		JSON_TO_NAMED(frames, _frames)
			to_json(j, static_cast<const AnimationData&>(t));
	}

	inline void from_json(const nlohmann::json& j, Animation2DData& t)
	{
		JSON_FROM_NAMED(frames, _frames)
			from_json(j, static_cast<AnimationData&>(t));
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const Coordinates& t)
	{
		to_json(j["position"], t.GetLocalPosition());
		to_json(j["center_of_rotation"], t.GetLocalCenterOfRotation());
		to_json(j["rotation"], t.GetLocalRotation());
		to_json(j["scale"], t.GetLocalScale());
	}

	inline void from_json(const nlohmann::json& j, Coordinates& t)
	{
		Quaternion q;
		Vector3 v;
		from_json(j.at("position"), v);
		t.SetLocalPosition(v);
		from_json(j.at("center_of_rotation"), v);
		t.SetLocalCenterOfRotation(v);
		from_json(j.at("rotation"), q);
		t.SetLocalRotation(q);
		from_json(j.at("scale"), v);
		t.SetLocalScale(v);
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const AutoTileTileSetData& t)
	{
		JSON_TO(id)
			to_json(j, t.tiles, "tiles");
	}

	inline void from_json(const nlohmann::json& j, AutoTileTileSetData& t)
	{
		JSON_FROM(id)

			//TODO : create template with factory
			for (auto it = j["tiles"].begin();
				it != j["tiles"].end();
				++it)
		{
			auto type = (*it).at("type").get<TileType>();

			switch (type)
			{
			case TileType::Static: { auto tile = new StaticTileData(); from_json(*it, *tile); t.tiles.push_back(tile); } break;
			case TileType::Animated: { auto tile = new AnimatedTileData(); from_json(*it, *tile); t.tiles.push_back(tile); } break;
			default: throw Exception("from_json(const nlohmann::json& j, AutoTileTileSetData& t) : type is not supported");
				//case TileType::Auto: { auto tile = new AutoTileData(); from_json(*it, *tile); t.tiles.push_back(tile); } break;
			}
		}
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const AutoTileSetData& t)
	{
		JSON_TO_NAMED(sprite_sheet_file_name, spriteSheetFileName)
			to_json(j["tile_size"], t.tileSize);
		to_json(j, t.sets, "sets");
	}

	inline void from_json(const nlohmann::json& j, AutoTileSetData& t)
	{
		JSON_FROM_NAMED(sprite_sheet_file_name, spriteSheetFileName)
			from_json(j["tile_size"], t.tileSize);
		from_json(j["sets"], t.sets);
	}

	//////////////////////////////////////////////////////////////

	NLOHMANN_JSON_SERIALIZE_ENUM(TileType, { {TileType::Static, "static"}, {TileType::Animated, "animated"}, {TileType::Auto, "auto"} })

		inline void to_json(nlohmann::json& j, const TileSetData& t)
	{
		JSON_TO_NAMED(sprite_sheet_file_name, spriteSheetFileName)
			to_json(j["tile_size"], t.tileSize);
		to_json(j, t.tiles, "tiles");
	}

	inline void from_json(const nlohmann::json& j, TileSetData& t)
	{
		JSON_FROM_NAMED(sprite_sheet_file_name, spriteSheetFileName)
			from_json(j["tile_size"], t.tileSize);

		//TODO : create template with factory
		for (auto it = j["tiles"].begin();
			it != j["tiles"].end();
			++it)
		{
			auto type = (*it).at("type").get<TileType>();

			switch (type)
			{
			case TileType::Static: { auto tile = new StaticTileData(); from_json(*it, *tile); t.tiles.push_back(tile); } break;
			case TileType::Animated: { auto tile = new AnimatedTileData(); from_json(*it, *tile); t.tiles.push_back(tile); } break;
			default: throw Exception("from_json(const nlohmann::json& j, TileSetData& t) : type is not supported");
				//case TileType::Auto: { auto tile = new AutoTileData(); from_json(*it, *tile); t.tiles.push_back(tile); } break;
			}
		}
	}

	//////////////////////////////////////////////////////////////

	NLOHMANN_JSON_SERIALIZE_ENUM(TileCollisionType, { {TileCollisionType::None, "none"}, {TileCollisionType::Blocked, "blocked"}, {TileCollisionType::NoContactResponse, "no_contact_response"} })

		inline void to_json(nlohmann::json& j, const TileData& t)
	{
		JSON_TO(type)
			JSON_TO(id)
			JSON_TO_NAMED(collision_type, collisionType)
			JSON_TO_NAMED(is_breakable, isBreakable)
	}

	inline void from_json(const nlohmann::json& j, TileData& t)
	{
		JSON_FROM(type)
			JSON_FROM(id)
			JSON_FROM_NAMED(collision_type, collisionType)
			JSON_FROM_NAMED(is_breakable, isBreakable)
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const StaticTileData& t)
	{
		JSON_TO_NAMED(sprite_id, spriteId)
			to_json(j, static_cast<const TileData&>(t));
	}

	inline void from_json(const nlohmann::json& j, StaticTileData& t)
	{
		JSON_FROM_NAMED(sprite_id, spriteId)
			from_json(j, static_cast<TileData&>(t));
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const AnimatedTileData& t)
	{
		JSON_TO_NAMED(animation_2d_id, animation2DId)
			to_json(j, static_cast<const TileData&>(t));
	}

	inline void from_json(const nlohmann::json& j, AnimatedTileData& t)
	{
		JSON_FROM_NAMED(animation_2d_id, animation2DId)
			from_json(j, static_cast<TileData&>(t));
	}

	//////////////////////////////////////////////////////////////

	//inline void to_json(nlohmann::json& j, const AutoTileData& t)
	//{
	//	JSON_TO_NAMED(asset_file_name, autoTileAssetName)
	//	to_json(j, static_cast<const TileData&>(t));
	//}
	//
	//inline void from_json(const nlohmann::json& j, AutoTileData& t)
	//{
	//	JSON_FROM_NAMED(asset_file_name, autoTileAssetName)
	//	from_json(j, static_cast<TileData&>(t));
	//}

	//////////////////////////////////////////////////////////////
	//factory
	inline void to_json(nlohmann::json& j, TileData* t)
	{
		if (t->type == TileType::Static)
		{
			to_json(j, *static_cast<StaticTileData*>(t));
		}
		else if (t->type == TileType::Animated)
		{
			to_json(j, *static_cast<AnimatedTileData*>(t));
		}
		//else if (t->type == TileType::Auto)
		//{
		//	to_json(j, *static_cast<AutoTileData*>(t));
		//}
		else
		{
			throw std::logic_error("void to_json(json& j, TileData* t) : type is not supported");
		}
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const TiledMapLayerData& t)
	{
		JSON_TO(type)
			JSON_TO_NAMED(z_offset, zOffset)
			JSON_TO_NAMED(tiles, tilesId)
	}

	inline void from_json(const nlohmann::json& j, TiledMapLayerData& t)
	{
		JSON_FROM(type)
			JSON_FROM_NAMED(z_offset, zOffset)
			JSON_FROM_NAMED(tiles, tilesId)
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const TiledMapData& t)
	{
		JSON_TO_NAMED(tile_set_file_name, tileSetFileName)
			JSON_TO_NAMED(auto_tile_set_file_name, autoTileSetFileName)
			to_json(j["coordinates"], t.coordinates);
		to_json(j["map_size"], t.mapSize);
		to_json(j, t.layers, "layers");
	}

	inline void from_json(const nlohmann::json& j, TiledMapData& t)
	{
		JSON_FROM_NAMED(tile_set_file_name, tileSetFileName)
			JSON_FROM_NAMED(auto_tile_set_file_name, autoTileSetFileName)
			from_json(j.at("coordinates"), t.coordinates);
		from_json(j.at("map_size"), t.mapSize);
		from_json(j.at("layers"), t.layers);
	}
}
