#pragma once

#include "Maths/Vector2.h"
#include "Maths/Vector3.h"
#include "Maths/Vector4.h"
#include "Maths/Rectangle.h"
#include "Maths/Quaternion.h"
#include <Assets/Assetable.h>
#include <Physics/Collision.h>
#include <Datas/SpriteData.h>
#include <Map2D/TileParameters.h>
#include "Datas/Animation2DData.h"
#include "Datas/AnimationData.h"
#include "Datas/FrameData.h"

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

	void to_json(nlohmann::json& j, TileParameters* t);
	DECLARE_SERIALIZABLE(TileParameters)
	DECLARE_SERIALIZABLE(StaticTileParameters)
	DECLARE_SERIALIZABLE(AnimatedTileParameters)
	DECLARE_SERIALIZABLE(AutoTileParameters)
	DECLARE_SERIALIZABLE(Animation2DData)

	template <class T>
	void to_json(nlohmann::json& j, const std::vector<T>& t, const char* name)
	{
		j.push_back(json::object_t::value_type(name, t));
	}

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
		j = json{ {"shape_type", t.Type()} };
	}

	inline void from_json(const nlohmann::json& j, IShape& t)
	{
		//do nothing
	}

	//////////////////////////////////////////////////////////////

	template <class T>
	void to_json(nlohmann::json& j, const CRectangle<T>& t)
	{
		JSON_TO(x)
		JSON_TO(y)
		JSON_TO(w)
		JSON_TO(h)
		to_json(j["shape"], static_cast<const IShape&>(t));
	}

	template <class T>
	void from_json(const nlohmann::json& j, CRectangle<T>& t)
	{
		JSON_FROM(x)
		JSON_FROM(y)
		JSON_FROM(w)
		JSON_FROM(h)
		from_json(j["shape"], static_cast<IShape&>(t));
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const IAssetable& t)
	{
		j = json{ {"asset_name", t.GetName()} };
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
		auto shapeType = (ShapeType)j.at("shape").at("shape_type").get<int>();

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
		j = json{ {"collision_type", t.GetType()} };
		to_json(j["shape"], t.GetShape());
	}

	inline void from_json(const nlohmann::json& j, Collision& t)
	{
		t.SetType((CollisionHitType)j.at("collision_type").get<int>());
		IShape* shape;
		from_json(j["shape"], &shape);
		t.SetShape(shape);
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const SpriteData& t)
	{
		j = json{ {"sprite_sheet", t.GetAssetFileName() } };
		to_json(j["location"], t.GetPositionInTexture());
		to_json(j["hotspot"], t.GetOrigin());
		to_json(j["collisions"], t._collisionShapes, "collision");
		to_json(j["asset"], static_cast<const IAssetable&>(t));
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
		from_json(j["asset"], static_cast<IAssetable&>(t));
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const FrameData& t)
	{
		j = json{ {"duration", t._duration, "sprite_id", t._spriteId} };
		to_json(j["asset"], static_cast<const IAssetable&>(t));
	}

	inline void from_json(const nlohmann::json& j, FrameData& t)
	{
		j.at("duration").get_to(t._duration);
		j.at("sprite_id").get_to(t._spriteId);
		from_json(j["asset"], static_cast<IAssetable&>(t));
	}

	//////////////////////////////////////////////////////////////

	NLOHMANN_JSON_SERIALIZE_ENUM(AnimationType, { {Once, "once"}, {PingPong, "pingPong"}, {Loop, "loop"} })

	inline void to_json(nlohmann::json& j, const AnimationData& t)
	{
		JSON_TO_NAMED(animation_type, _animationType)
		to_json(j["asset"], static_cast<const IAssetable&>(t));
	}

	inline void from_json(const nlohmann::json& j, AnimationData& t)
	{
		JSON_FROM_NAMED(animation_type, _animationType)
		from_json(j["asset"], static_cast<IAssetable&>(t));
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
		from_json(j["anim"], static_cast<AnimationData&>(t));
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const Coordinates& t)
	{
		to_json(j["position"], t.GetLocalPosition());
		to_json(j["center_of_rotation"], t.GetCenterOfRotation());
		to_json(j["rotation"], t.GetRotation());
		to_json(j["scale"], t.GetLocalScale());
	}

	inline void from_json(const nlohmann::json& j, Coordinates& t)
	{
		Quaternion q;
		Vector3 v;
		from_json(j.at("position"), v);
		t.SetLocalPosition(v);
		from_json(j.at("center_of_rotation"), v);
		t.SetCenterOfRotation(v);
		from_json(j.at("rotation"), q);
		t.SetLocalRotation(q);
		from_json(j.at("scale"), v);
		t.SetLocalScale(v);
	}

	//////////////////////////////////////////////////////////////

	//NLOHMANN_JSON_SERIALIZE_ENUM(TileType, { {TileType::Static, "static"}, {TileType::Animated, "animated"}, {TileType::Auto, "auto"} })

	inline void to_json(nlohmann::json& j, const TileParameters& t)
	{
		JSON_TO(type)
		JSON_TO(x)
		JSON_TO(y)
	}

	inline void from_json(const nlohmann::json& j, TileParameters& t)
	{
		JSON_FROM(type)
		JSON_FROM(x)
		JSON_FROM(y)
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const StaticTileParameters& t)
	{
		JSON_TO_NAMED(sprite_id, spriteId)
		to_json(j, static_cast<const TileParameters&>(t));
	}

	inline void from_json(const nlohmann::json& j, StaticTileParameters& t)
	{
		JSON_FROM_NAMED(sprite_id, spriteId)
		from_json(j, static_cast<TileParameters&>(t));
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const AnimatedTileParameters& t)
	{
		JSON_TO_NAMED(animation_2d_id, animation2DId)
		to_json(j, static_cast<const TileParameters&>(t));
	}

	inline void from_json(const nlohmann::json& j, AnimatedTileParameters& t)
	{
		JSON_FROM_NAMED(animation_2d_id, animation2DId)
		from_json(j, static_cast<TileParameters&>(t));
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const AutoTileParameters& t)
	{
		JSON_TO_NAMED(asset_file_name, autoTileAssetName)
		to_json(j, static_cast<const TileParameters&>(t));
	}

	inline void from_json(const nlohmann::json& j, AutoTileParameters& t)
	{
		JSON_FROM_NAMED(asset_file_name, autoTileAssetName)
		from_json(j, static_cast<TileParameters&>(t));
	}

	//////////////////////////////////////////////////////////////
	//factory
	inline void to_json(nlohmann::json& j, TileParameters* t)
	{
		if (t->type == TileType::Static)
		{
			to_json(j, *static_cast<StaticTileParameters*>(t));
		}
		else if (t->type == TileType::Animated)
		{
			to_json(j, *static_cast<AnimatedTileParameters*>(t));
		}
		else if (t->type == TileType::Auto)
		{
			to_json(j, *static_cast<AutoTileParameters*>(t));
		}
		else
		{
			throw std::logic_error("void to_json(json& j, TileParameters* t) : type is not supported");
		}
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const TiledMapLayerParameters& t)
	{
		JSON_TO_NAMED(z_offset, zOffset)
		to_json(j, t.tiles, "tiles");
	}

	inline void from_json(const nlohmann::json& j, TiledMapLayerParameters& t)
	{
		JSON_FROM_NAMED(z_offset, zOffset)
		//from_json(j["tiles"], t.tiles);

		for (auto it = j["tiles"].begin();
			it != j["tiles"].end();
			++it)
		{
			auto type = (*it).at("type").get<TileType>();

			switch (type)
			{
			case TileType::Static: { auto tile = new StaticTileParameters(); from_json(*it, *tile); t.tiles.push_back(tile); } break;
			case TileType::Animated: { auto tile = new AnimatedTileParameters(); from_json(*it, *tile); t.tiles.push_back(tile); } break;
			case TileType::Auto: { auto tile = new AutoTileParameters(); from_json(*it, *tile); t.tiles.push_back(tile); } break;
			}
		}
	}

	//////////////////////////////////////////////////////////////

	inline void to_json(nlohmann::json& j, const TiledMapParameters& t)
	{
		to_json(j["coordinates"], t.coordinates);
		to_json(j["map_size"], t.mapSize);
		to_json(j["tile_size"], t.tileSize);
		to_json(j, t.layers, "layers");
	}

	inline void from_json(const nlohmann::json& j, TiledMapParameters& t)
	{
		//j["name"].get<std::string>()

		from_json(j.at("coordinates"), t.coordinates);
		from_json(j.at("map_size"), t.mapSize);
		from_json(j.at("tile_size"), t.tileSize);
		from_json(j.at("layers"), t.layers);
	}
}
