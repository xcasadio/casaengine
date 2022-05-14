#include "StaticTile.h"

namespace CasaEngine
{
	StaticTile::StaticTile(Sprite* pSprite) :
		m_pSprite(pSprite)
	{

	}

	void StaticTile::Update(const GameTime& gameTime_)
	{
		//do nothing
	}

	void StaticTile::Draw(float x, float y, float z)
	{
		if (m_pSprite != nullptr)
		{
			auto uv_offset = m_pSprite->GetSpriteData()->GetPositionInTexture();
			uv_offset.x = 0.0f;
			uv_offset.y = 0.0f;
			ITile::Draw(m_pSprite, x, y, z, uv_offset);
		}
	}

	void StaticTile::Draw(float x, float y, float z, Rectangle uvOffset)
	{
		if (m_pSprite != nullptr)
		{
			ITile::Draw(m_pSprite, x, y, z, uvOffset);
		}
	}

	Sprite* StaticTile::GetSprite() const
	{
		return m_pSprite;
	}

	void StaticTile::setSprite(Sprite* const pSprite)
	{
		m_pSprite = pSprite;
	}
}
