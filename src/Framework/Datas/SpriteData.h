#pragma once

#include "CA_Export.h"
#include "Maths/Rectangle.h"
#include "Maths/Vector2.h"
#include "Assets/Assetable.h"
#include <Physics/Collision.h>

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

	private:
		Rectangle m_PositionInTexture;
		Vector2I m_Origin;
		//std::vector<Vector2I> m_Sockets;
		std::string m_AssetFileName;
	};
}