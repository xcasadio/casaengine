#pragma once

#include  "Tile.hpp"
#include  "Datas/TileSetData.hpp"
#include  "Sprite/Sprite.hpp"

namespace CasaEngine
{
	class CA_EXPORT StaticTile : public ITile
	{
	public:
		explicit StaticTile(Sprite* pSprite, StaticTileData *tileData);
		~StaticTile() override = default;

		void Update(const GameTime& gameTime_) override;
		void Draw(float x, float y, float z) override;
		void Draw(float x, float y, float z, const Rectangle& uvOffset) override;

		Sprite* GetSprite() const;
		void setSprite(Sprite* const sprite);
		TileData* GetTileData() override;

	private:
		Sprite* _sprite;
		StaticTileData* _tileData;
	};
}
