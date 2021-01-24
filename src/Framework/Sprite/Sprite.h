#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "CA_Export.h"
#include "Graphics/Textures/Texture.h"
#include "Maths/Rectangle.h"
#include "Maths/Vector2.h"

#include <string>
#include "Maths/Shape/IShape.h"
#include <Datas/SpriteData.h>

namespace CasaEngine
{
	class CA_EXPORT Sprite
	{
	private:
		static std::map<std::string, Texture*> _textureCache;

	public:
		Sprite::Sprite(SpriteData& spriteData);
		~Sprite() = default;

		Texture* GetTexture2D() const;
		SpriteData* GetSpriteData() const;

	private:
		Texture* m_pTexture2D;
		SpriteData *m_pSpriteData;
	};
}

#endif
