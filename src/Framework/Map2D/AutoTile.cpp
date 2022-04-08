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

	AutoTile::AutoTile(TiledMapLayer* pLayer, int x, int y) : m_pLayer(pLayer), m_x(x), m_y(y), m_Hidden(false)
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

	unsigned int getMask(TiledMapLayer* pLayer, int x, int y, int offset)
	{
		const AutoTile* pTile = dynamic_cast<AutoTile*>(pLayer->GetTile(x, y));
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

	void AutoTile::Draw(float x, float y, float z, RectangleI uvOffset)
	{
		unsigned int mask = 0;
		mask |= getMask(m_pLayer, m_x - 1, m_y, 0);
		mask |= getMask(m_pLayer, m_x + 1, m_y, 1);
		mask |= getMask(m_pLayer, m_x, m_y - 1, 2);
		mask |= getMask(m_pLayer, m_x, m_y + 1, 3);
		mask |= getMask(m_pLayer, m_x - 1, m_y - 1, 4);
		mask |= getMask(m_pLayer, m_x - 1, m_y + 1, 5);
		mask |= getMask(m_pLayer, m_x + 1, m_y - 1, 6);
		mask |= getMask(m_pLayer, m_x + 1, m_y + 1, 7);

		DrawTile(mask, x, y, z, uvOffset);
	}

	void AutoTile::DrawTile(unsigned int mask, float x, float y, float z, const RectangleI uv_offset) const
	{
		//trivial case
		if (mask == mask_none)
		{
			m_Tiles[0]->Draw(x, y, z, uv_offset);
			return;
		}

		const auto width = uv_offset.w / 2.0f;
		const auto height = uv_offset.h / 2.0f;

		//trivial case
		if (mask == mask_all)
		{
			m_Tiles[2]->Draw(x, y, z, RectangleI(width, height, width, height));
			m_Tiles[3]->Draw(x + width, y, z, RectangleI(0, height, width, height));
			m_Tiles[4]->Draw(x, y + height, z, RectangleI(width, 0, width, height));
			m_Tiles[5]->Draw(x + width, y + height, z, RectangleI(0, 0, width, height));
			return;
		}

		unsigned int mask1 = 0;

		mask1 = mask & (mask_left_top | mask_top | mask_left);
		//left-top sub tile
		if (mask1 == (mask_left_top | mask_top | mask_left))
		{
			m_Tiles[2]->Draw(x, y, z, RectangleI(width, height, width, height));
		}
		else if (mask1 == (mask_left_top | mask_left))
		{
			m_Tiles[2]->Draw(x, y, z, RectangleI(width, 0, width, height));
		}
		else if (mask1 == (mask_left_top | mask_top)
			|| mask1 == mask_top)
		{
			m_Tiles[4]->Draw(x, y, z, RectangleI(0, 0, width, height));
		}
		else if (mask1 == (mask_top | mask_left))
		{
			m_Tiles[1]->Draw(x, y, z, RectangleI(0, 0, width, height));
		}
		else if (mask1 == mask_left_top || mask1 == 0)
		{
			m_Tiles[0]->Draw(x, y, z, RectangleI(0, 0, width, height));
		}
		else if (mask1 == mask_left)
		{
			m_Tiles[3]->Draw(x, y, z, RectangleI(0, 0, width, height));
		}

		x += width;
		mask1 = mask & (mask_right_top | mask_top | mask_right);
		//right-top sub tile
		if (mask1 == (mask_right_top | mask_top | mask_right))
		{
			m_Tiles[3]->Draw(x, y, z, RectangleI(0, height, width, height));
		}
		else if (mask1 == (mask_right_top | mask_right))
		{
			m_Tiles[3]->Draw(x, y, z, RectangleI(0, 0, width, height));
		}
		else if (mask1 == (mask_right_top | mask_top)
			|| mask1 == mask_top)
		{
			m_Tiles[3]->Draw(x, y, z, RectangleI(width, height, width, height));
		}
		else if (mask1 == (mask_top | mask_right))
		{
			m_Tiles[1]->Draw(x, y, z, RectangleI(width, 0, width, height));
		}
		else if (mask1 == mask_right_top || mask1 == 0)
		{
			m_Tiles[0]->Draw(x, y, z, RectangleI(width, 0, width, height));
		}
		else if (mask1 == mask_right)
		{
			m_Tiles[2]->Draw(x, y, z, RectangleI(width, 0, width, height));
		}

		x -= width;
		y += height;
		mask1 = mask & (mask_left_bottom | mask_bottom | mask_left);
		//left-bottom sub tile
		if (mask1 == (mask_left_bottom | mask_bottom | mask_left))
		{
			m_Tiles[4]->Draw(x, y, z, RectangleI(width, 0, width, height));
		}
		else if (mask1 == (mask_left_bottom | mask_left)
			|| (mask1 == mask_left))
		{
			m_Tiles[4]->Draw(x, y, z, RectangleI(width, height, width, height));
		}
		else if (mask1 == (mask_left_bottom | mask_bottom)
			|| mask1 == mask_bottom)
		{
			m_Tiles[2]->Draw(x, y, z, RectangleI(0, height, width, height));
		}
		else if (mask1 == (mask_bottom | mask_left))
		{
			m_Tiles[1]->Draw(x, y, z, RectangleI(0, height, width, height));
		}
		else if (mask1 == mask_left_bottom || mask1 == 0)
		{
			m_Tiles[0]->Draw(x, y, z, RectangleI(0, height, width, height));
		}

		x += width;
		//y += height;
		mask1 = mask & (mask_right_bottom | mask_bottom | mask_right);
		//right-bottom sub tile
		if (mask1 == (mask_right_bottom | mask_bottom | mask_right))
		{
			m_Tiles[5]->Draw(x, y, z, RectangleI(0, 0, width, height));
		}
		else if (mask1 == (mask_right_bottom | mask_right))
		{
			m_Tiles[4]->Draw(x, y, z, RectangleI(width, height, width, height));
		}
		else if (mask1 == (mask_right_bottom | mask_bottom)
			|| mask1 == mask_bottom)
		{
			m_Tiles[3]->Draw(x, y, z, RectangleI(width, height, width, height));
		}
		else if (mask1 == (mask_bottom | mask_right))
		{
			m_Tiles[1]->Draw(x, y, z, RectangleI(width, height, width, height));
		}
		else if (mask1 == mask_right_bottom || mask1 == 0)
		{
			m_Tiles[0]->Draw(x, y, z, RectangleI(width, height, width, height));
		}
		else if (mask1 == mask_right)
		{
			m_Tiles[4]->Draw(x, y, z, RectangleI(width, height, width, height));
		}
	}
}
