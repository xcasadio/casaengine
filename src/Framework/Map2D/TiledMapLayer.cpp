#include "TiledMapLayer.h"
#include "TiledMapComponent.h"
#include "Assets/AssetManager.h"
#include "Entities/ComponentTypeEnum.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"
#include "Sprite/SpriteRenderer.h"

namespace CasaEngine
{
	TiledMapLayer::TiledMapLayer()
	{
	}

	void TiledMapLayer::Initialize()
	{
		for (auto* tile : m_Tiles)
		{
			if (tile != nullptr)
			{
				tile->Initialize();
			}
		}
	}

	void TiledMapLayer::Update(const GameTime& gameTime_)
	{
		for (auto* tile : m_Tiles)
		{
			if (tile != nullptr)
			{
				tile->Update(gameTime_);
			}
		}
	}

	void TiledMapLayer::Draw(Transform3DComponent* pTransform3DComponent, float z)
	{
		const auto world_matrix = pTransform3DComponent->GetWorldMatrix();
		const float px = world_matrix.GetTranslation().x;
		const float py = world_matrix.GetTranslation().y;

		for (int y = 0; y < m_MapSize.y; ++y)
		{
			for (int x = 0; x < m_MapSize.x; ++x)
			{
				if (m_Tiles[x + y * m_MapSize.x] != nullptr)
				{
					m_Tiles[x + y * m_MapSize.x]->Draw(
						px + x * m_TileSize.x, py + y * m_TileSize.y, z,
						RectangleI(0, 0, m_TileSize.x, m_TileSize.y));
				}
			}
		}
	}

	Vector2I TiledMapLayer::GetMapSize() const
	{
		return m_MapSize;
	}

	void TiledMapLayer::SetMapSize(Vector2I& size)
	{
		m_MapSize = size;
	}

	Vector2I TiledMapLayer::GetTileSize() const
	{
		return m_TileSize;
	}

	void TiledMapLayer::SetTileSize(Vector2I& size)
	{
		m_TileSize = size;
	}

	std::vector<ITile*> TiledMapLayer::GetTiles() const
	{
		return m_Tiles;
	}

	void TiledMapLayer::SetTiles(std::vector<ITile*>& tiles)
	{
		m_Tiles.clear();

		for (auto* tile : tiles)
		{
			m_Tiles.push_back(tile);
		}
	}

	void TiledMapLayer::SetTile(int x, int y, ITile* pTile)
	{
		m_Tiles[x + y * m_MapSize.x] = pTile;
	}

	ITile* TiledMapLayer::GetTile(const int x, const int y) const
	{
		if (x >= m_MapSize.x || x < 0
			|| y >= m_MapSize.y || y < 0)
		{
			return nullptr;
		}

		//check limits
		return m_Tiles[x + y * m_MapSize.x];
	}
}