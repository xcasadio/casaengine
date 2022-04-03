#ifndef AUTO_TILE_H_
#define AUTO_TILE_H_

#include <vector>

#include "Tile.h"
#include "TiledMapComponent.h"

namespace CasaEngine
{
	class CA_EXPORT AutoTile : public ITile
	{
	public:
		AutoTile(TiledMapLayer* pLayer, int x, int y);
		~AutoTile() = default;
		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw(float x, float y, float z, RectangleI uvOffset) override;
		std::vector<ITile*> getTiles() const;
		void setTiles(const std::vector<ITile*>& m_tiles);
		bool Hidden() const;

	private:
		void DrawTile(unsigned mask, float x, float y, float z, RectangleI uvOffset);

	private:
		std::vector<ITile*> m_Tiles;
		TiledMapLayer* m_pLayer;
		const int m_x, m_y;
		bool m_Hidden;
	};
}

#endif
