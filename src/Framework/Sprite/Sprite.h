#pragma once

#include "CA_Export.h"
#include "Graphics/Textures/Texture.h"
#include <Datas/SpriteData.h>

#include <string>

namespace CasaEngine
{
	class CA_EXPORT Sprite
	{
	public:
		Sprite(SpriteData& spriteData);

		Texture* GetTexture2D() const;
		SpriteData* GetSpriteData() const;

	private:
		static std::map<std::string, Texture*> _textureCache;

		Texture* _texture2D;
		SpriteData* _spriteData;
	};
}
