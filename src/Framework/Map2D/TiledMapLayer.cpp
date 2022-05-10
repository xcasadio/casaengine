#include "TiledMapLayer.h"
#include "TiledMapComponent.h"
#include "Game/Game.h"
#include "Maths/Shape/Circle.h"
#include "Physics/Bullet/BulletObjectsContainer.h"
#include "Sprite/SpriteRenderer.h"
#include "Physics/CollisionParameters.h"

namespace CasaEngine
{
	TiledMapLayer::TiledMapLayer():
		_zOffset(0)
	{
	}

	void TiledMapLayer::Initialize(BaseEntity* entity)
	{
		for (auto* tile : _tiles)
		{
			if (tile != nullptr)
			{
				tile->Initialize();
			}
		}

		auto* physicsWorld = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld();

		for (int y = 0; y < _mapSize.y; ++y)
		{
			for (int x = 0; x < _mapSize.x; ++x)
			{
				auto* tile = _tiles[x + y * _mapSize.x];
				if (tile != nullptr && tile->IsWall())
				{
					auto *shape = new Rectangle(0, 0, _tileSize.x, _tileSize.y);
					//auto *shape = new Circle(m_TileSize.x);
					auto position = Vector3(x * _tileSize.x + _tileSize.x / 2.0f, y * _tileSize.y + _tileSize.y / 2.0f, 0.0f);
					auto *collisionShape = physicsWorld->CreateCollisionShape(entity, shape, position, CollisionHitType::Unknown, CollisionFlags::Static);
					physicsWorld->AddCollisionObject(collisionShape);
				}
			}
		}
	}

	void TiledMapLayer::Update(const GameTime& gameTime_)
	{
		for (auto* tile : _tiles)
		{
			if (tile != nullptr)
			{
				tile->Update(gameTime_);
			}
		}
	}

	void TiledMapLayer::Draw(const Vector3& translation)
	{
		const float px = translation.x;
		const float py = translation.y;
		const float z = translation.z;

		for (int y = 0; y < _mapSize.y; ++y)
		{
			for (int x = 0; x < _mapSize.x; ++x)
			{
				if (_tiles[x + y * _mapSize.x] != nullptr)
				{
					_tiles[x + y * _mapSize.x]->Draw(
						px + x * _tileSize.x, 
						py + y * _tileSize.y, 
						z + _zOffset,
						RectangleI(0, 0, _tileSize.x, _tileSize.y));
				}
			}
		}
	}

	Vector2I TiledMapLayer::GetMapSize() const
	{
		return _mapSize;
	}

	void TiledMapLayer::SetMapSize(Vector2I& size)
	{
		_mapSize = size;
	}

	Vector2I TiledMapLayer::GetTileSize() const
	{
		return _tileSize;
	}

	void TiledMapLayer::SetTileSize(Vector2I& size)
	{
		_tileSize = size;
	}

	std::vector<ITile*> TiledMapLayer::GetTiles() const
	{
		return _tiles;
	}

	void TiledMapLayer::SetTiles(std::vector<ITile*>& tiles)
	{
		_tiles.clear();

		for (auto* tile : tiles)
		{
			_tiles.push_back(tile);
		}
	}

	void TiledMapLayer::SetTile(int x, int y, ITile* pTile)
	{
		_tiles[x + y * _mapSize.x] = pTile;
	}

	ITile* TiledMapLayer::GetTile(const int x, const int y) const
	{
		if (x >= _mapSize.x || x < 0
			|| y >= _mapSize.y || y < 0)
		{
			return nullptr;
		}

		return _tiles[x + y * _mapSize.x];
	}

	void TiledMapLayer::SetZOffset(float value)
	{
		_zOffset = value;
	}

	float TiledMapLayer::GetZOffset() const
	{
		return _zOffset;
	}
}
