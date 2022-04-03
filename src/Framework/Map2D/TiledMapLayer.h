#ifndef TILEDMAPLAYER_H_
#define TILEDMAPLAYER_H_

#include <vector>

#include "Tile.h"
#include "Animations/Animation2D.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Maths/Vector2.h"

namespace CasaEngine
{
	class TiledMapComponent;

	class CA_EXPORT TiledMapLayer : public AllocatedObject<TiledMapLayer>
	{
	public:
		TiledMapLayer();

		void Initialize(BaseEntity* pEntity);
		void Update(const GameTime& gameTime_);
		void Draw(Transform3DComponent* pTransform3DComponent, float z);

		Vector2I GetMapSize() const;
		void SetMapSize(Vector2I& size);

		Vector2I GetTileSize() const;
		void SetTileSize(Vector2I& size);

		std::vector<ITile*> GetTiles() const;
		void SetTiles(std::vector<ITile*>& tiles);

		void SetTile(int x, int y, ITile* pTile);
		ITile* GetTile(int x, int y) const;

	private:
		Vector2I m_MapSize;
		Vector2I m_TileSize;
		std::vector<ITile*> m_Tiles;
	};
}

#endif
