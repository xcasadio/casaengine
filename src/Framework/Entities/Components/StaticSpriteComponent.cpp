#include "Base.h"
#include "Entities/BaseEntity.h"

#include "StaticSpriteComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include <string>
#include "Game/Game.h"
#include "Sprite/SpriteRenderer.h"
#include "Sprite/SpriteTypes.h"
#include "Graphics/Color.h"
#include "Assets/AssetManager.h"

namespace CasaEngine
{
	StaticSpriteComponent::StaticSpriteComponent(BaseEntity* pEntity_)
		: Component(pEntity_, STATIC_SPRITE),
		_spriteRenderer(nullptr),
		_sprite(nullptr)
	{

	}

	StaticSpriteComponent::~StaticSpriteComponent()
	{

	}

	std::string StaticSpriteComponent::GetSpriteID() const
	{
		return _spriteId;
	}

	void StaticSpriteComponent::SetSpriteID(std::string val)
	{
		_spriteId = val;
		_sprite = new Sprite(*Game::Instance().GetAssetManager().GetAsset<SpriteData>(_spriteId));
	}

	Color StaticSpriteComponent::GetColor() const
	{
		return _color;
	}

	void StaticSpriteComponent::SetColor(Color val)
	{
		_color = val;
	}

	eSpriteEffects StaticSpriteComponent::GetSpriteEffect() const
	{
		return _spriteEffect;
	}

	void StaticSpriteComponent::SetSpriteEffect(eSpriteEffects val)
	{
		_spriteEffect = val;
	}

	void StaticSpriteComponent::Initialize()
	{
		_spriteRenderer = Game::Instance().GetGameComponent<SpriteRenderer>();
		CA_ASSERT(_spriteRenderer != nullptr, "StaticSpriteComponent::Initialize() can't find the component SpriteRenderer");
	}

	void StaticSpriteComponent::Update(const GameTime& /*gameTime_*/)
	{
	}

	void StaticSpriteComponent::Draw()
	{
		_spriteRenderer->AddSprite(_sprite, GetEntity()->GetCoordinates().GetWorldMatrix(), _color, _spriteEffect);
	}
}
