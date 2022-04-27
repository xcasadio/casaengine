#pragma once

#include <vector>

#include "Tile.h"
#include "Animations/Animation2D.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Maths/Vector2.h"
#include "Maths/Vector3.h"

namespace CasaEngine
{
	class TiledMapComponent;

	class CA_EXPORT TiledMapLayer
	{
	public:
		TiledMapLayer();

		void Initialize(BaseEntity* pEntity);
		void Update(const GameTime& gameTime_);
		void Draw(const Vector3& translation);

		Vector2I GetMapSize() const;
		void SetMapSize(Vector2I& size);

		Vector2I GetTileSize() const;
		void SetTileSize(Vector2I& size);

		std::vector<ITile*> GetTiles() const;
		void SetTiles(std::vector<ITile*>& tiles);

		void SetTile(int x, int y, ITile* pTile);
		ITile* GetTile(int x, int y) const;

		void SetZOffset(float value);
		float GetZOffset() const;

	private:
		Vector2I m_MapSize;
		Vector2I m_TileSize;
		std::vector<ITile*> m_Tiles;
		float zOffset;
	};
}
