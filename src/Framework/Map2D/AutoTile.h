#pragma once

#include <vector>

#include "Tile.h"
#include "TiledMapLayer.h"
#include "TileParameters.h"
#include "Datas/AutoTileSetData.h"
#include "Maths/Rectangle.h"

namespace CasaEngine
{
	struct CA_EXPORT AutoTileDrawingInfo
	{
		int tileIndex;
		float x_offset, y_offset, z_offset;
		RectangleI posInTexture;

		void SetInfo(int tileIndex_, float x_offset_, float y_offset_, float z_offset_, const RectangleI& posInTexture_);
	};


	class CA_EXPORT AutoTile : public ITile
	{
	public:
		AutoTile(AutoTileSetData* data);
		~AutoTile();

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw(float x, float y, float z) override;
		void Draw(float x, float y, float z, RectangleI uvOffset) override;

		void SetTileInfo(TiledMapParameters* map, TiledMapLayerParameters* layer, int x, int y);

		bool Hidden() const;

	private:
		void ComputeDrawingInfos(unsigned int mask, float x, float y, float z, const RectangleI uv_offset);

		AutoTileSetData* _autoTileSetData;
		TiledMapLayerParameters* _layerParameters;
		TiledMapParameters* _mapParameters;
		AutoTileDrawingInfo _drawingInfos[4];
		ITile* _tiles[6];
		int _x, _y;
		bool _hidden;
	};
}
