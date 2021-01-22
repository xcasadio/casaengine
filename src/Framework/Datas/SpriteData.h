#ifndef _SPRITEDATA_H_
#define _SPRITEDATA_H_

#include "CA_Export.h"
#include "Maths/Rectangle.h"
#include "Maths/Vector2.h"

#include <string>
#include "Assets/Assetable.h"
#include <iosfwd>
#include "Maths/Shape/IShape.h"

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <Sprite/Collision.h>

namespace CasaEngine
{
	class CA_EXPORT SpriteData :
		public IAssetable
	{
	public:
		SpriteData();
		~SpriteData();

		RectangleI GetPositionInTexture() const;
		Vector2I GetOrigin() const;
		std::string GetAssetFileName() const;
		void Clear();

		std::vector<Collision>& GetCollisions();

		//#if EDITOR
		void SetPositionInTexture(RectangleI val);
		void SetOrigin(Vector2I val);
		void SetAssetFileName(std::string val);
		//#endif // EDITOR

	private:
		RectangleI m_PositionInTexture;
		Vector2I m_Origin;
		std::vector<Collision> m_CollisionShapes;
		//std::vector<Vector2I> m_Sockets;
		std::string m_AssetFileName;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAssetable>(this));
			ar(cereal::make_nvp("texture_name", m_AssetFileName));
			ar(cereal::make_nvp("uv", m_PositionInTexture));
			ar(cereal::make_nvp("hotspot", m_Origin));
			//ar(cereal::make_nvp("collisions", m_CollisionShapes));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAssetable>(this));
			ar(cereal::make_nvp("texture_name", m_AssetFileName));
			ar(cereal::make_nvp("uv", m_PositionInTexture));
			ar(cereal::make_nvp("hotspot", m_Origin));
			//ar(cereal::make_nvp("collisions", m_CollisionShapes));
		}
	};
}

#endif
