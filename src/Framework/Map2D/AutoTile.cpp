#include "AutoTile.h"

#include "StaticTile.h"
#include "Game/Game.h"

namespace CasaEngine
{
	void AutoTileDrawingInfo::SetInfo(int tileIndex_, float x_offset_, float y_offset_, float z_offset_, const Rectangle& posInTexture_)
	{
		tileIndex = tileIndex_;
		x_offset = x_offset_;
		y_offset = y_offset_;
		z_offset = z_offset_;
		posInTexture = posInTexture_;
	}

	constexpr unsigned int mask_none = 0;
	constexpr unsigned int mask_left = 1 << 0;
	constexpr unsigned int mask_right = 1 << 1;
	constexpr unsigned int mask_top = 1 << 2;
	constexpr unsigned int mask_bottom = 1 << 3;
	constexpr unsigned int mask_left_top = 1 << 4;
	constexpr unsigned int mask_left_bottom = 1 << 5;
	constexpr unsigned int mask_right_top = 1 << 6;
	constexpr unsigned int mask_right_bottom = 1 << 7;
	constexpr unsigned int mask_all = (mask_left | mask_right | mask_top | mask_bottom | mask_left_top | mask_left_bottom | mask_right_top | mask_right_bottom);

	AutoTile::AutoTile(TileData* tileData) :
		_tiledMapLayerData(nullptr),
		_tileData(tileData),
		_drawingInfos{},
		_tiles{},
		_x(0),
		_y(0),
		_hidden(false)
	{
	}

	AutoTile::~AutoTile() = default;

	bool AutoTile::Hidden() const
	{
		return _hidden;
	}

	void AutoTile::RemovedTileFromLayer()
	{
		_tiledMapLayerData->tilesId[_x + _y * _mapSize.x] = -1;
	}

	void AutoTile::Initialize()
	{
		ITile::Initialize();

		for (auto& _tile : _tiles)
		{
			_tile->Initialize();
		}

		_drawingInfos[0].SetInfo(-1, 0, 0, 0, Rectangle());
		_drawingInfos[1].SetInfo(-1, 0, 0, 0, Rectangle());
		_drawingInfos[2].SetInfo(-1, 0, 0, 0, Rectangle());
		_drawingInfos[3].SetInfo(-1, 0, 0, 0, Rectangle());
	}

	unsigned int getMask(const Vector2I& mapSize, const TiledMapLayerData* layer, int x, int y, int offset)
	{
		if (x >= mapSize.x || x < 0
			|| y >= mapSize.y || y < 0)
		{
			return 0;
		}

		const auto tileId = layer->tilesId.at(x + y * mapSize.x);
		if (tileId != -1)
		{
			return  1 << offset;
		}

		return 0;
	}

	void AutoTile::Update(const GameTime& gameTime_)
	{
		for (auto* tile : _tiles)
		{
			tile->Update(gameTime_);
		}

		unsigned int mask = 0;
		mask |= getMask(_mapSize, _tiledMapLayerData, _x - 1, _y, 0);
		mask |= getMask(_mapSize, _tiledMapLayerData, _x + 1, _y, 1);
		mask |= getMask(_mapSize, _tiledMapLayerData, _x, _y - 1, 2);
		mask |= getMask(_mapSize, _tiledMapLayerData, _x, _y + 1, 3);
		mask |= getMask(_mapSize, _tiledMapLayerData, _x - 1, _y - 1, 4);
		mask |= getMask(_mapSize, _tiledMapLayerData, _x - 1, _y + 1, 5);
		mask |= getMask(_mapSize, _tiledMapLayerData, _x + 1, _y - 1, 6);
		mask |= getMask(_mapSize, _tiledMapLayerData, _x + 1, _y + 1, 7);

		ComputeDrawingInfos(mask, 0, 0, 0, Rectangle(0, 0, _tileSize.x, _tileSize.y));
	}

	void AutoTile::Draw(float x, float y, float z)
	{
		Draw(x, y, z, Rectangle(0, 0, _tileSize.x, _tileSize.y));
	}

	void AutoTile::Draw(float x, float y, float z, const Rectangle& uvOffset)
	{
		for (const auto& drawingInfo : _drawingInfos)
		{
			if (drawingInfo.tileIndex != -1)
			{
				_tiles[drawingInfo.tileIndex]->Draw(
					x + drawingInfo.x_offset,
					y + drawingInfo.y_offset,
					z + drawingInfo.z_offset,
					drawingInfo.posInTexture);
			}
		}
	}

	TileData* AutoTile::GetTileData()
	{
		return _tileData;
	}

	void AutoTile::SetTileInfo(const std::vector<ITile*>& tiles, const Vector2I& tileSize, const Vector2I& mapSize, TiledMapLayerData* layer, int x, int y)
	{
		CA_ASSERT(tiles.size() == 6, "AutoTile::SetTileInfo() : size is not 6")

		for (int i = 0; i < 6; ++i)
		{
			CA_ASSERT(tiles[i] != nullptr, "AutoTile::SetTileInfo() : ITile is null")
			_tiles[i] = tiles[i];
		}

		_tileSize = tileSize;
		_mapSize = mapSize;
		_tiledMapLayerData = layer;
		_x = x;
		_y = y;
	}

	void AutoTile::ComputeDrawingInfos(unsigned int mask, float x, float y, float z, const Rectangle uv_offset)
	{
		_drawingInfos[0].SetInfo(-1, x, y, z, uv_offset);
		_drawingInfos[1].SetInfo(-1, x, y, z, uv_offset);
		_drawingInfos[2].SetInfo(-1, x, y, z, uv_offset);
		_drawingInfos[3].SetInfo(-1, x, y, z, uv_offset);

		//trivial case
		if (mask == mask_none)
		{
			_drawingInfos[0].SetInfo(0, x, y, z, uv_offset);
			return;
		}

		const auto width = uv_offset.w / 2.0f;
		const auto height = uv_offset.h / 2.0f;

		//trivial case
		if (mask == mask_all)
		{
			_drawingInfos[0].SetInfo(2, x, y, z, Rectangle(width, height, width, height));
			_drawingInfos[1].SetInfo(3, x + width, y, z, Rectangle(0, height, width, height));
			_drawingInfos[2].SetInfo(4, x, y + height, z, Rectangle(width, 0, width, height));
			_drawingInfos[3].SetInfo(5, x + width, y + height, z, Rectangle(0, 0, width, height));
			return;
		}

		int index = 0;
		unsigned int mask1 = 0;

		mask1 = mask & (mask_left_top | mask_top | mask_left);
		//left-top sub tile
		if (mask1 == (mask_left_top | mask_top | mask_left))
		{
			_drawingInfos[index++].SetInfo(2, x, y, z, Rectangle(width, height, width, height));
		}
		else if (mask1 == (mask_left_top | mask_left))
		{
			_drawingInfos[index++].SetInfo(2, x, y, z, Rectangle(width, 0, width, height));
		}
		else if (mask1 == (mask_left_top | mask_top)
			|| mask1 == mask_top)
		{
			_drawingInfos[index++].SetInfo(4, x, y, z, Rectangle(0, 0, width, height));
		}
		else if (mask1 == (mask_top | mask_left))
		{
			_drawingInfos[index++].SetInfo(1, x, y, z, Rectangle(0, 0, width, height));
		}
		else if (mask1 == mask_left_top || mask1 == 0)
		{
			_drawingInfos[index++].SetInfo(0, x, y, z, Rectangle(0, 0, width, height));
		}
		else if (mask1 == mask_left)
		{
			_drawingInfos[index++].SetInfo(3, x, y, z, Rectangle(0, 0, width, height));
		}

		x += width;
		mask1 = mask & (mask_right_top | mask_top | mask_right);
		//right-top sub tile
		if (mask1 == (mask_right_top | mask_top | mask_right))
		{
			_drawingInfos[index++].SetInfo(3, x, y, z, Rectangle(0, height, width, height));
		}
		else if (mask1 == (mask_right_top | mask_right))
		{
			_drawingInfos[index++].SetInfo(3, x, y, z, Rectangle(0, 0, width, height));
		}
		else if (mask1 == (mask_right_top | mask_top)
			|| mask1 == mask_top)
		{
			_drawingInfos[index++].SetInfo(3, x, y, z, Rectangle(width, height, width, height));
		}
		else if (mask1 == (mask_top | mask_right))
		{
			_drawingInfos[index++].SetInfo(1, x, y, z, Rectangle(width, 0, width, height));
		}
		else if (mask1 == mask_right_top || mask1 == 0)
		{
			_drawingInfos[index++].SetInfo(0, x, y, z, Rectangle(width, 0, width, height));
		}
		else if (mask1 == mask_right)
		{
			_drawingInfos[index++].SetInfo(2, x, y, z, Rectangle(width, 0, width, height));
		}

		x -= width;
		y += height;
		mask1 = mask & (mask_left_bottom | mask_bottom | mask_left);
		//left-bottom sub tile
		if (mask1 == (mask_left_bottom | mask_bottom | mask_left))
		{
			_drawingInfos[index++].SetInfo(4, x, y, z, Rectangle(width, 0, width, height));
		}
		else if (mask1 == (mask_left_bottom | mask_left)
			|| (mask1 == mask_left))
		{
			_drawingInfos[index++].SetInfo(4, x, y, z, Rectangle(width, height, width, height));
		}
		else if (mask1 == (mask_left_bottom | mask_bottom)
			|| mask1 == mask_bottom)
		{
			_drawingInfos[index++].SetInfo(2, x, y, z, Rectangle(0, height, width, height));
		}
		else if (mask1 == (mask_bottom | mask_left))
		{
			_drawingInfos[index++].SetInfo(1, x, y, z, Rectangle(0, height, width, height));
		}
		else if (mask1 == mask_left_bottom || mask1 == 0)
		{
			_drawingInfos[index++].SetInfo(0, x, y, z, Rectangle(0, height, width, height));
		}

		x += width;
		//y += height;
		mask1 = mask & (mask_right_bottom | mask_bottom | mask_right);
		//right-bottom sub tile
		if (mask1 == (mask_right_bottom | mask_bottom | mask_right))
		{
			_drawingInfos[index++].SetInfo(5, x, y, z, Rectangle(0, 0, width, height));
		}
		else if (mask1 == (mask_right_bottom | mask_right))
		{
			_drawingInfos[index++].SetInfo(4, x, y, z, Rectangle(width, height, width, height));
		}
		else if (mask1 == (mask_right_bottom | mask_bottom)
			|| mask1 == mask_bottom)
		{
			_drawingInfos[index++].SetInfo(3, x, y, z, Rectangle(width, height, width, height));
		}
		else if (mask1 == (mask_bottom | mask_right))
		{
			_drawingInfos[index++].SetInfo(1, x, y, z, Rectangle(width, height, width, height));
		}
		else if (mask1 == mask_right_bottom || mask1 == 0)
		{
			_drawingInfos[index++].SetInfo(0, x, y, z, Rectangle(width, height, width, height));
		}
		else if (mask1 == mask_right)
		{
			_drawingInfos[index++].SetInfo(4, x, y, z, Rectangle(width, height, width, height));
		}
	}
}
