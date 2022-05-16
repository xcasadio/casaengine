#pragma once

#include "Tile.h"
#include "Datas/TileData.h"
#include "Datas/AutoTileSetData.h"
#include "Maths/Rectangle.h"

namespace CasaEngine
{
	//internal usage
	struct CA_EXPORT AutoTileDrawingInfo
	{
		int tileIndex;
		float x_offset, y_offset, z_offset;
		Rectangle posInTexture;

		void SetInfo(int tileIndex_, float x_offset_, float y_offset_, float z_offset_, const Rectangle& posInTexture_);
	};

	/////////////////////////////////////////

	class CA_EXPORT AutoTile : public ITile
	{
	public:
		AutoTile();
		~AutoTile() override;

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw(float x, float y, float z) override;
		void Draw(float x, float y, float z, const Rectangle& uvOffset) override;

		void SetTileInfo(const std::vector<ITile*>& tiles, const Vector2I& tileSize, const Vector2I& mapSize, TiledMapLayerData* layer, int x, int y);

		bool Hidden() const;

		void RemovedTileFromLayer(); //TODO in other class ?

	private:
		void ComputeDrawingInfos(unsigned int mask, float x, float y, float z, const Rectangle uv_offset);

		Vector2I _tileSize;
		TiledMapLayerData* _tiledMapLayerData;
		Vector2I _mapSize;
		AutoTileDrawingInfo _drawingInfos[4];
		ITile* _tiles[6];
		int _x, _y;
		bool _hidden;
	};
}
