#include  "TileComponent.hpp"

#include  "Entities/ComponentTypeEnum.hpp"
#include  "Game/Game.hpp"

namespace CasaEngine
{
	TileComponent::TileComponent(BaseEntity* entity_)
		: Component(entity_, ComponentType::TILE),
		_tile(nullptr)
	{
	}

	void TileComponent::Initialize()
	{
		_tile->Initialize();
	}

	void TileComponent::Update(const GameTime& gameTime_)
	{
		_tile->Update(gameTime_);
	}

	void TileComponent::Draw()
	{
		const auto translation = GetEntity()->GetCoordinates().GetWorldMatrix().Translation();
		_tile->Draw(translation.x, translation.y, translation.z);
	}

	ITile* TileComponent::Tile() const
	{
		return _tile;
	}

	void TileComponent::Tile(ITile* val)
	{
		_tile = val;
	}

}
