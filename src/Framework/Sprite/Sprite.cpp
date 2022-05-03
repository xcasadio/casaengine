#include "Sprite/Sprite.h"

#include "Game/Game.h"
#include "Graphics/Textures/Texture.h"

namespace CasaEngine
{
	std::map<std::string, Texture*> Sprite::_textureCache;

	Sprite::Sprite(SpriteData& spriteData)
	{
		Texture* texture;
		auto pair = _textureCache.find(spriteData.GetAssetFileName());

		if (pair != _textureCache.end())
		{
			texture = pair->second;
		}
		else
		{
			auto* textureFile = Game::Instance().GetMediaManager().FindMedia(spriteData.GetAssetFileName().c_str(), true);
			texture = Texture::loadTexture(textureFile);
			_textureCache.insert(std::make_pair(spriteData.GetAssetFileName(), texture));
		}

		m_pTexture2D = texture;
		m_pSpriteData = &spriteData;
	}

	Texture* Sprite::GetTexture2D() const
	{
		return m_pTexture2D;
	}

	SpriteData* Sprite::GetSpriteData() const
	{
		return m_pSpriteData;
	}
}
