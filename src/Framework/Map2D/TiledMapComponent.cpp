#include "TiledMapComponent.h"

#include "Assets/AssetManager.h"
#include "Entities/ComponentTypeEnum.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"

namespace CasaEngine
{
	TiledMapComponent::TiledMapComponent(BaseEntity* pEntity_)
		: Component(pEntity_, ComponentType::TILED_MAP)
		, m_pTransform3DComponent(nullptr)
	{
	}

	void TiledMapComponent::Initialize()
	{
		m_pTransform3DComponent = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
		CA_ASSERT(m_pTransform3DComponent != nullptr, "entity must contain a Transform3DComponent")
		
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
		float zOrder = 0.0f;
		for (auto* pLayer : m_Layers)
		{
			pLayer->Draw(m_pTransform3DComponent, m_pTransform3DComponent->GetPosition().z + zOrder);
			zOrder += 0.01f;
		}
	}

	Vector2I TiledMapComponent::GetMapSize() const
	{
		return m_MapSize;
	}

	void TiledMapComponent::SetMapSize(Vector2I& size)
	{
		m_MapSize = size;
	}

	Vector2I TiledMapComponent::GetTileSize() const
	{
		return m_TileSize;
	}

	void TiledMapComponent::SetTileSize(Vector2I& size)
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

	TiledMapLayer* TiledMapComponent::GetLayer(const int layerNum) const
	{
		return m_Layers[layerNum];
	}
}
