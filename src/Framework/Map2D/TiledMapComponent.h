#ifndef TILEDMAP_H_
#define TILEDMAP_H_

#include <vector>

#include "Tile.h"
#include "Animations/Animation2D.h"
#include "Entities/Component.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Maths/Vector2.h"
#include "Sprite/Sprite.h"
#include "Sprite/SpriteRenderer.h"

namespace CasaEngine
{
	class CA_EXPORT TiledMapComponent :
		public Component
	{
	public:
		TiledMapComponent(BaseEntity* pEntity_);

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		Vector2I GetMapSize() const;
		void SetMapSize(Vector2I& size);

		Vector2I GetTileSize() const;
		void SetTileSize(Vector2I& size);

		std::vector<ITile*> GetTiles()  const;
		void SetTiles(std::vector<ITile*>& tiles);

		void SetTile(int x, int y, ITile* pTile);
		ITile* GetTile(const int x, const int y) const;

	private:
		Vector2I m_MapSize;
		Vector2I m_TileSize;
		std::vector<ITile*> m_Tiles;

		SpriteRenderer* m_pSpriteRenderer;
		Transform3DComponent* m_pTransform3DComponent;
	};
}

#endif // TILEDMAP_H_
