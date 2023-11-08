#include  "Base.hpp"
#include  "Entities/BaseEntity.hpp"

#include  "StaticSpriteComponent.hpp"
#include  "Maths/Matrix4.hpp"
#include  "Entities/ComponentTypeEnum.hpp"
#include <string>
#include  "Game/Game.hpp"
#include  "Sprite/SpriteRenderer.hpp"
#include  "Sprite/SpriteTypes.hpp"
#include  "Graphics/Color.hpp"
#include  "Assets/AssetManager.hpp"

namespace CasaEngine
{
	StaticSpriteComponent::StaticSpriteComponent(BaseEntity* entity)
		: Component(entity, STATIC_SPRITE),
		_spriteRenderer(nullptr),
		_sprite(nullptr)
	{

	}

	StaticSpriteComponent::~StaticSpriteComponent()
		= default;

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
