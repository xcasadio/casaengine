#include "AnimatedTile.h"

#include "Assets/AssetManager.h"
#include "Game/Game.h"
#include "Sprite/Sprite.h"

namespace CasaEngine
{
	AnimatedTile::AnimatedTile(Animation2D* animation, AnimatedTileData* tileData) :
		_animation(animation),
		_tileData(tileData)
	{
	}

	void AnimatedTile::Initialize()
	{
		ITile::Initialize();

		CA_ASSERT(_animation != nullptr, "animation 2D is null");
		_animation->Initialize();
	}

	void AnimatedTile::Update(const GameTime& gameTime_)
	{
		if (_animation != nullptr)
		{
			_animation->Update(gameTime_.FrameTime());
		}
	}

	void AnimatedTile::Draw(float x, float y, float z)
	{
		if (_animation != nullptr)
		{
			//TODO : load all sprite in initialization function
			auto* pSprite = new Sprite(*Game::Instance().GetAssetManager().GetAsset<SpriteData>(_animation->CurrentFrame()));
			ITile::Draw(pSprite, x, y, z, pSprite->GetSpriteData()->GetPositionInTexture());
		}
	}

	void AnimatedTile::Draw(float x, float y, float z, const Rectangle& uvOffset)
	{
		if (_animation != nullptr)
		{
			//TODO : load all sprite in initialization function
			auto* pSprite = new Sprite(*Game::Instance().GetAssetManager().GetAsset<SpriteData>(_animation->CurrentFrame()));
			ITile::Draw(pSprite, x, y, z, uvOffset);
		}
	}

	TileData* AnimatedTile::GetTileData()
	{
		return _tileData;
	}

	Animation2D* AnimatedTile::GetAnimation() const
	{
		return _animation;
	}

	void AnimatedTile::SetAnimation(Animation2D* const pAnimation)
	{
		_animation = pAnimation;
	}
}
