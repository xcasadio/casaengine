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

	void StaticTile::Draw(float x, float y, float z, RectangleI uvOffset)
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
