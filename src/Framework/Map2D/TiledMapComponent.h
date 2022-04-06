#ifndef TILEDMAPCOMPONENT_H_
#define TILEDMAPCOMPONENT_H_

#include <vector>

#include "TiledMapLayer.h"
#include "Animations/Animation2D.h"
#include "Entities/Component.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Maths/Vector2.h"

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
		void SetMapSize(const Vector2I& size);

		Vector2I GetTileSize() const;
		void SetTileSize(const Vector2I& size);

		std::vector<TiledMapLayer*> GetLayers()  const;

		void AddLayer(TiledMapLayer *pLayer);
		TiledMapLayer* GetLayer(int layerNum) const;

	private:
		Vector2I m_MapSize;
		Vector2I m_TileSize;
		std::vector<TiledMapLayer*> m_Layers;
		Transform3DComponent* m_pTransform3DComponent;
	};
}

#endif
