#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "CA_Export.h"
#include "Graphics/Textures/Texture.h"

#include <string>
#include <Datas/SpriteData.h>

namespace CasaEngine
{
	class CA_EXPORT Sprite : public AllocatedObject<Sprite>
	{
	private:
		static std::map<std::string, Texture*> _textureCache;

	public:
		Sprite(SpriteData& spriteData);

		Texture* GetTexture2D() const;
		SpriteData* GetSpriteData() const;

	private:
		Texture* m_pTexture2D;
		SpriteData *m_pSpriteData;
	};
}

#endif
