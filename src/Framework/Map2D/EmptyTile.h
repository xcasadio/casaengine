#pragma once

#include "Tile.h"

namespace CasaEngine
{
	class CA_EXPORT EmptyTile : public ITile
	{
	public:
		explicit EmptyTile() = default;
		~EmptyTile() override = default;

		void Update(const GameTime& gameTime_) override;
		void Draw(float x, float y, float z) override;
		void Draw(float x, float y, float z, const Rectangle& uvOffset) override;
		TileData* GetTileData() override;
	};
}
