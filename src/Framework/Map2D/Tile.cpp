#include "Tile.h"

namespace CasaEngine
{
	ITile::ITile() : m_IsWall(false)
	{
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

	void ITile::Draw(const Sprite* sprite, float x, float y, float z, RectangleI uvOffset) const
	{
		const RectangleI texUV = RectangleI(
			sprite->GetSpriteData()->GetPositionInTexture().Left() + uvOffset.Left(),
			sprite->GetSpriteData()->GetPositionInTexture().Top() + uvOffset.Top(),
			uvOffset.w,
			uvOffset.h);

		m_pSpriteRenderer->AddSprite(
			sprite->GetTexture2D(),
			texUV,
			sprite->GetSpriteData()->GetOrigin(),
			Vector2(x, y),
			0.0f,
			Vector2::One(),
			Color::White,
			z);
	}
}
