#include "Tile.h"

namespace CasaEngine
{
	void ITile::Initialize()
	{
		m_pSpriteRenderer = Game::Instance().GetGameComponent<SpriteRenderer>();
		CA_ASSERT(m_pSpriteRenderer != nullptr);
	}

	void ITile::Draw(Sprite* pSprite, float x, float y, float z, CRectangleI& textCoordOffset) const
	{
		const CRectangleI texUV = CRectangleI(
			pSprite->GetPositionInTexture().Left() + textCoordOffset.Left(),
			pSprite->GetPositionInTexture().Top() + textCoordOffset.Top(),
			textCoordOffset.w,
			textCoordOffset.h);

		m_pSpriteRenderer->AddSprite(
			pSprite->GetTexture2D(),
			texUV,
			pSprite->GetOrigin(),
			Vector2F(x, y),
			0.0f,
			Vector2F(texUV.w, texUV.h),
			CColor::White,
			z);
	}
}
