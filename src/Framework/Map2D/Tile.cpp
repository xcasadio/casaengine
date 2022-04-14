#include "Tile.h"

namespace CasaEngine
{
	ITile::ITile()
	{
		m_IsWall = false;
	}
	
	void ITile::Initialize()
	{
		m_pSpriteRenderer = Game::Instance().GetGameComponent<SpriteRenderer>();
		CA_ASSERT(m_pSpriteRenderer != nullptr);
	}

	void ITile::IsWall(bool val)
	{
		m_IsWall = val;
	}

	bool ITile::IsWall() const
	{
		return m_IsWall;
	}

	void ITile::Draw(Sprite* pSprite, float x, float y, float z, RectangleI uvOffset) const
	{
		const RectangleI texUV = RectangleI(
			pSprite->GetSpriteData()->GetPositionInTexture().Left() + uvOffset.Left(),
			pSprite->GetSpriteData()->GetPositionInTexture().Top() + uvOffset.Top(),
			uvOffset.w,
			uvOffset.h);

		m_pSpriteRenderer->AddSprite(
			pSprite->GetTexture2D(),
			texUV,
			pSprite->GetSpriteData()->GetOrigin(),
			Vector2(x, y),
			0.0f,
			Vector2::One(),
			Color::White,
			z);
	}
}
