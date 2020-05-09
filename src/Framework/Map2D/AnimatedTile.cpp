#include "AnimatedTile.h"

#include "Assets/AssetManager.h"
#include "Game/Game.h"
#include "Sprite/Sprite.h"
#include "Sprite/SpriteRenderer.h"

namespace CasaEngine
{
	AnimatedTile::AnimatedTile(Animation2D* pAnimation) :
		m_pAnimation(pAnimation)
	{
	}

	void AnimatedTile::Initialize()
	{
		ITile::Initialize();

		CA_ASSERT(m_pAnimation != nullptr);
		m_pAnimation->Initialize();
	}

	void AnimatedTile::Update(const GameTime& gameTime_)
	{
		if (m_pAnimation != nullptr)
		{
			m_pAnimation->Update(gameTime_.FrameTime());
		}
	}

	void AnimatedTile::Draw(float x, float y, float z, CRectangleI& textCoordOffset)
	{
		if (m_pAnimation != nullptr)
		{
			auto* pSprite = Game::Instance().GetAssetManager().GetAsset<Sprite>(m_pAnimation->CurrentFrame());
			ITile::Draw(pSprite, x, y, z, textCoordOffset);
		}
	}

	Animation2D* AnimatedTile::GetAnimation() const
	{
		return m_pAnimation;
	}

	void AnimatedTile::SetAnimation(Animation2D* const pAnimation)
	{
		m_pAnimation = pAnimation;
	}
}
