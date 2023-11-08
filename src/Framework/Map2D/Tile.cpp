#include  "Tile.hpp"

#include  "Game/Game.hpp"

namespace CasaEngine
{
	ITile::ITile() = default;

	void ITile::Initialize()
	{
		_spriteRenderer = Game::Instance().GetGameComponent<SpriteRenderer>();
		CA_ASSERT(_spriteRenderer != nullptr, "ITile::Initialize SpriteRenderer is null")
	}

	void ITile::Draw(const Sprite* sprite, float x, float y, float z, const Rectangle& uvOffset) const
	{
		const Rectangle texUV = Rectangle(
			sprite->GetSpriteData()->GetPositionInTexture().Left() + uvOffset.Left(),
			sprite->GetSpriteData()->GetPositionInTexture().Top() + uvOffset.Top(),
			uvOffset.w,
			uvOffset.h);

		_spriteRenderer->AddSprite(
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
