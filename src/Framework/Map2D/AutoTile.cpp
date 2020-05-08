#include "AutoTile.h"

#include "TiledMapComponent.h"

namespace CasaEngine
{

	const unsigned int mask_none = 0;
	const unsigned int mask_left = 1 << 0;
	const unsigned int mask_right = 1 << 1;
	const unsigned int mask_top = 1 << 2;
	const unsigned int mask_bottom = 1 << 3;
	const unsigned int mask_left_top = 1 << 4;
	const unsigned int mask_left_bottom = 1 << 5;
	const unsigned int mask_right_top = 1 << 6;
	const unsigned int mask_right_bottom = 1 << 7;
	const unsigned int mask_all = (mask_left | mask_right | mask_top | mask_bottom | mask_left_top | mask_left_bottom | mask_right_top | mask_right_bottom);

	AutoTile::AutoTile(TiledMapComponent* map, int x, int y) : m_Map(map), m_x(x), m_y(y), m_Hidden(false)
	{
	}

	std::vector<ITile*> AutoTile::getTiles() const
	{
		return m_Tiles;
	}

	void AutoTile::setTiles(const std::vector<ITile*>& m_tiles)
	{
		m_Tiles = m_tiles;
	}

	bool AutoTile::Hidden() const
	{
		return m_Hidden;
	}

	void AutoTile::Initialize()
	{
		ITile::Initialize();

		for (auto* tile : m_Tiles)
		{
			tile->Initialize();
		}
	}

	unsigned int getMask(TiledMapComponent* pMap, int x, int y, int offset)
	{
		const AutoTile* pTile = dynamic_cast<AutoTile*>(pMap->GetTile(x, y));
		if (pTile != nullptr && pTile->Hidden() == false)
		{
			return  1 << offset;
		}

		return 0;
	}

	void AutoTile::Update(const GameTime& gameTime_)
	{
		for (auto* tile : m_Tiles)
		{
			tile->Update(gameTime_);
		}
	}

	void AutoTile::Draw(float x, float y, float z, CRectangleI& textCoordOffset)
	{
		unsigned int mask = 0;
		mask |= getMask(m_Map, m_x - 1, m_y, 0);
		mask |= getMask(m_Map, m_x + 1, m_y, 1);
		mask |= getMask(m_Map, m_x, m_y - 1, 2);
		mask |= getMask(m_Map, m_x, m_y + 1, 3);
		mask |= getMask(m_Map, m_x - 1, m_y - 1, 4);
		mask |= getMask(m_Map, m_x - 1, m_y + 1, 5);
		mask |= getMask(m_Map, m_x + 1, m_y - 1, 6);
		mask |= getMask(m_Map, m_x + 1, m_y + 1, 7);

		DrawTile(mask, x, y, z, textCoordOffset);
	}

	void AutoTile::DrawTile(unsigned int mask, float x, float y, float z, CRectangleI& textCoordOffset)
	{
		//trivial case
		if (mask == mask_none)
		{
			m_Tiles[0]->Draw(x, y, z, textCoordOffset);
			return;
		}

		const auto width = textCoordOffset.w / 2;
		const auto height = textCoordOffset.h / 2;

		//trivial case
		if (mask == mask_all)
		{
			m_Tiles[2]->Draw(x, y, z, CRectangleI(width, height, width, height));
			m_Tiles[3]->Draw(x + width, y, z, CRectangleI(0, height, width, height));
			m_Tiles[4]->Draw(x, y + height, z, CRectangleI(width, 0, width, height));
			m_Tiles[5]->Draw(x + width, y + height, z, CRectangleI(0, 0, width, height));
			return;
		}

		unsigned int mask1 = 0;

		mask1 = mask & (mask_left_top | mask_top | mask_left);
		//left-top sub tile
		if (mask1 == (mask_left_top | mask_top | mask_left))
		{
			m_Tiles[2]->Draw(x, y, z, CRectangleI(width, height, width, height));
		}
		else if (mask1 == (mask_left_top | mask_left))
		{
			m_Tiles[2]->Draw(x, y, z, CRectangleI(width, 0, width, height));
		}
		else if (mask1 == (mask_left_top | mask_top)
			|| mask1 == mask_top)
		{
			m_Tiles[4]->Draw(x, y, z, CRectangleI(0, 0, width, height));
		}
		else if (mask1 == (mask_top | mask_left))
		{
			m_Tiles[1]->Draw(x, y, z, CRectangleI(0, 0, width, height));
		}
		else if (mask1 == mask_left_top || mask1 == 0)
		{
			m_Tiles[0]->Draw(x, y, z, CRectangleI(0, 0, width, height));
		}
		else if (mask1 == mask_left)
		{
			m_Tiles[3]->Draw(x, y, z, CRectangleI(0, 0, width, height));
		}

		x += width;
		mask1 = mask & (mask_right_top | mask_top | mask_right);
		//right-top sub tile
		if (mask1 == (mask_right_top | mask_top | mask_right))
		{
			m_Tiles[3]->Draw(x, y, z, CRectangleI(0, height, width, height));
		}
		else if (mask1 == (mask_right_top | mask_right))
		{
			m_Tiles[3]->Draw(x, y, z, CRectangleI(0, 0, width, height));
		}
		else if (mask1 == (mask_right_top | mask_top)
			|| mask1 == mask_top)
		{
			m_Tiles[3]->Draw(x, y, z, CRectangleI(width, height, width, height));
		}
		else if (mask1 == (mask_top | mask_right))
		{
			m_Tiles[1]->Draw(x, y, z, CRectangleI(width, 0, width, height));
		}
		else if (mask1 == mask_right_top || mask1 == 0)
		{
			m_Tiles[0]->Draw(x, y, z, CRectangleI(width, 0, width, height));
		}
		else if (mask1 == mask_right)
		{
			m_Tiles[2]->Draw(x, y, z, CRectangleI(width, 0, width, height));
		}

		x -= width;
		y += height;
		mask1 = mask & (mask_left_bottom | mask_bottom | mask_left);
		//left-bottom sub tile
		if (mask1 == (mask_left_bottom | mask_bottom | mask_left))
		{
			m_Tiles[4]->Draw(x, y, z, CRectangleI(width, 0, width, height));
		}
		else if (mask1 == (mask_left_bottom | mask_left)
			|| (mask1 == mask_left))
		{
			m_Tiles[4]->Draw(x, y, z, CRectangleI(width, height, width, height));
		}
		else if (mask1 == (mask_left_bottom | mask_bottom)
			|| mask1 == mask_bottom)
		{
			m_Tiles[2]->Draw(x, y, z, CRectangleI(0, height, width, height));
		}
		else if (mask1 == (mask_bottom | mask_left))
		{
			m_Tiles[1]->Draw(x, y, z, CRectangleI(0, height, width, height));
		}
		else if (mask1 == mask_left_bottom || mask1 == 0)
		{
			m_Tiles[0]->Draw(x, y, z, CRectangleI(0, height, width, height));
		}

		x += width;
		//y += height;
		mask1 = mask & (mask_right_bottom | mask_bottom | mask_right);
		//right-bottom sub tile
		if (mask1 == (mask_right_bottom | mask_bottom | mask_right))
		{
			m_Tiles[5]->Draw(x, y, z, CRectangleI(0, 0, width, height));
		}
		else if (mask1 == (mask_right_bottom | mask_right))
		{
			m_Tiles[4]->Draw(x, y, z, CRectangleI(width, height, width, height));
		}
		else if (mask1 == (mask_right_bottom | mask_bottom)
			|| mask1 == mask_bottom)
		{
			m_Tiles[3]->Draw(x, y, z, CRectangleI(width, height, width, height));
		}
		else if (mask1 == (mask_bottom | mask_right))
		{
			m_Tiles[1]->Draw(x, y, z, CRectangleI(width, height, width, height));
		}
		else if (mask1 == mask_right_bottom || mask1 == 0)
		{
			m_Tiles[0]->Draw(x, y, z, CRectangleI(width, height, width, height));
		}
		else if (mask1 == mask_right)
		{
			m_Tiles[4]->Draw(x, y, z, CRectangleI(width, height, width, height));
		}
	}
}
