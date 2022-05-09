#include "TiledMapComponent.h"

#include "Assets/AssetManager.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"

namespace CasaEngine
{
	TiledMapComponent::TiledMapComponent(BaseEntity* pEntity_)
		: Component(pEntity_, ComponentType::TILED_MAP)
	{
	}

	void TiledMapComponent::Initialize()
	{
		for (auto* pLayer : m_Layers)
		{
			pLayer->Initialize(GetEntity());
		}
	}

	void TiledMapComponent::Update(const GameTime& gameTime_)
	{
		for (auto* pLayer : m_Layers)
		{
			pLayer->Update(gameTime_);
		}
	}

	void TiledMapComponent::Draw()
	{
		const auto translation = GetEntity()->GetCoordinates().GetWorldMatrix().Translation();

		for (auto* pLayer : m_Layers)
		{
			pLayer->Draw(translation);
		}
	}

	Vector2I TiledMapComponent::GetMapSize() const
	{
		return m_MapSize;
	}

	void TiledMapComponent::SetMapSize(const Vector2I& size)
	{
		m_MapSize = size;
	}

	Vector2I TiledMapComponent::GetTileSize() const
	{
		return m_TileSize;
	}

	void TiledMapComponent::SetTileSize(const Vector2I& size)
	{
		m_TileSize = size;
	}

	std::vector<TiledMapLayer*> TiledMapComponent::GetLayers() const
	{
		return m_Layers;
	}

	void TiledMapComponent::AddLayer(TiledMapLayer *pLayer)
	{
		pLayer->SetTileSize(m_TileSize);
		pLayer->SetMapSize(m_MapSize);
		m_Layers.push_back(pLayer);
	}

	TiledMapLayer* TiledMapComponent::GetLayer(int layerNum) const
	{
		return m_Layers[layerNum];
	}
}
