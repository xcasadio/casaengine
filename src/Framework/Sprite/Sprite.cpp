#include  "Sprite/Sprite.hpp"

#include  "Game/Game.hpp"
#include  "Graphics/Textures/Texture.hpp"

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

		_texture2D = texture;
		_spriteData = &spriteData;
	}

	Texture* Sprite::GetTexture2D() const
	{
		return _texture2D;
	}

	SpriteData* Sprite::GetSpriteData() const
	{
		return _spriteData;
	}
}
