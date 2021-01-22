#include "Tile.h"

namespace CasaEngine
{
	void ITile::Initialize()
	{
		m_pSpriteRenderer = Game::Instance().GetGameComponent<SpriteRenderer>();
		CA_ASSERT(m_pSpriteRenderer != nullptr);
	}

	void ITile::Draw(Sprite* pSprite, float x, float y, float z, RectangleI uvOffset) const
	{
		const RectangleI texUV = RectangleI(
			pSprite->GetPositionInTexture().Left() + uvOffset.Left(),
			pSprite->GetPositionInTexture().Top() + uvOffset.Top(),
			uvOffset.w,
			uvOffset.h);

		m_pSpriteRenderer->AddSprite(
			pSprite->GetTexture2D(),
			texUV,
			pSprite->GetOrigin(),
			Vector2F(x, y),
			0.0f,
			Vector2F::One(),
			CColor::White,
			z);
	}
}
