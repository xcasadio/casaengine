#include "StaticTile.h"

namespace CasaEngine
{
	StaticTile::StaticTile(Sprite* pSprite, StaticTileData* tileData) :
		_sprite(pSprite),
		_tileData(tileData)
	{

	}

	void StaticTile::Update(const GameTime& gameTime_)
	{
		//do nothing
	}

	void StaticTile::Draw(float x, float y, float z)
	{
		if (_sprite != nullptr)
		{
			auto uv_offset = _sprite->GetSpriteData()->GetPositionInTexture();
			uv_offset.x = 0.0f;
			uv_offset.y = 0.0f;
			ITile::Draw(_sprite, x, y, z, uv_offset);
		}
	}

	void StaticTile::Draw(float x, float y, float z, const Rectangle& uvOffset)
	{
		if (_sprite != nullptr)
		{
			ITile::Draw(_sprite, x, y, z, uvOffset);
		}
	}

	Sprite* StaticTile::GetSprite() const
	{
		return _sprite;
	}

	void StaticTile::setSprite(Sprite* const sprite)
	{
		_sprite = sprite;
	}

	TileData* StaticTile::GetTileData()
	{
		return _tileData;
	}
}
