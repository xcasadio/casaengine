#pragma once

#include "CA_Export.hpp"
#include  "Maths/Rectangle.hpp"
#include  "Maths/Vector2.hpp"
#include  "Assets/Assetable.hpp"
#include <Physics/Collision.hpp>

#include <string>
#include <vector>

namespace CasaEngine
{
	class CA_EXPORT SpriteData :
		public IAssetable
	{
	public:
		SpriteData();
		SpriteData(const SpriteData& rsh);
		SpriteData& operator=(const SpriteData& rsh);
		~SpriteData() override;
		SpriteData(SpriteData&& rsh) = default;
		SpriteData& operator=(SpriteData&& rsh) = default;

		Rectangle GetPositionInTexture() const;
		Vector2I GetOrigin() const;
		std::string GetAssetFileName() const;
		void Clear();

		std::vector<Collision> _collisionShapes;

		SpriteData* Copy() const;

		//#if EDITOR
		void SetPositionInTexture(Rectangle val);
		void SetOrigin(Vector2I val);
		void SetAssetFileName(std::string val);
		//#endif

		bool operator ==(const SpriteData& rsh) const;

	private:
		Rectangle _positionInTexture;
		Vector2I _origin;
		//std::vector<Vector2I> m_Sockets;
		std::string _assetFileName;
	};

}