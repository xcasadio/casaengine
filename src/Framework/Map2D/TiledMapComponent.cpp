#include "TiledMapComponent.h"

#include "Assets/AssetManager.h"
#include "Entities/ComponentTypeEnum.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"
#include "Sprite/SpriteRenderer.h"

namespace CasaEngine
{
	TiledMapComponent::TiledMapComponent(BaseEntity* pEntity_)
		: Component(pEntity_, ComponentType::TILED_MAP)
		, m_pSpriteRenderer(nullptr)
		, m_pTransform3DComponent(nullptr)
	{
	}

	void TiledMapComponent::Initialize()
	{
		m_pSpriteRenderer = Game::Instance()->GetGameComponent<SpriteRenderer>();
		CA_ASSERT(m_pSpriteRenderer != nullptr);

		m_pTransform3DComponent = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
		CA_ASSERT(m_pTransform3DComponent != nullptr);

		for (auto* anim : m_Tiles)
		{
			if (anim != nullptr)
			{
				anim->Initialize();
			}
		}
	}

	void TiledMapComponent::Update(const GameTime& gameTime_)
	{
		for (auto* anim : m_Tiles)
		{
			if (anim != nullptr)
			{
				anim->Update(gameTime_);
			}
		}
	}

	void TiledMapComponent::Draw()
	{
		auto world_matrix = m_pTransform3DComponent->GetWorldMatrix();
		const float px = world_matrix.GetTranslation().x;
		const float py = world_matrix.GetTranslation().y;
		const float z = world_matrix.GetTranslation().z;

		for (int y = 0; y < m_MapSize.y; ++y)
		{
			for (int x = 0; x < m_MapSize.x; ++x)
			{
				if (m_Tiles[x + y * m_MapSize.x] != nullptr)
				{
					m_Tiles[x + y * m_MapSize.x]->Draw(
						px + x * m_TileSize.x, py + y * m_TileSize.y, z,
						CRectangleI(0, 0, m_TileSize.x, m_TileSize.y));

					/*Animation2D& anim = *m_Tiles[x + y * m_MapSize.x];
					world_matrix.SetTranslation(Vector3F(px + x * m_TileSize.x, py + y * m_TileSize.y, z));
					auto* spriteName = anim.CurrentFrame();
					m_pSpriteRenderer->AddSprite(AssetManager::Instance().GetAsset<Sprite>(spriteName),
						world_matrix,
						CColor::White,
						z,
						eSpriteEffects::SPRITE_EFFECT_NONE);*/
				}
			}
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

	std::vector<ITile*> TiledMapComponent::GetTiles() const
	{
		return m_Tiles;
	}

	void TiledMapComponent::SetTiles(std::vector<ITile*>& tiles)
	{
		m_Tiles.clear();

		for (auto* tile : tiles)
		{
			m_Tiles.push_back(tile);
		}
	}

	void TiledMapComponent::SetTile(int x, int y, ITile* pTile)
	{
		m_Tiles[x + y * m_MapSize.x] = pTile;
	}

	ITile* TiledMapComponent::GetTile(const int x, const int y) const
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
