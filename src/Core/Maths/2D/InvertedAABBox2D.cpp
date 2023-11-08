#include  "InvertedAABBox2D.hpp"

namespace CasaEngine
{
	InvertedAABBox2D::InvertedAABBox2D(Vector2 tl,
		Vector2 br) :m_vTopLeft(tl),
		m_vBottomRight(br),
		m_vCenter((tl + br) / 2.0)
	{}

	//returns true if the bbox described by other intersects with this one
	bool InvertedAABBox2D::isOverlappedWith(const InvertedAABBox2D& other)const
	{
		return !(other.Top() > this->Bottom() ||
			other.Bottom() < this->Top() ||
			other.Left() > this->Right() ||
			other.Right() < this->Left());
	}

	Vector2 InvertedAABBox2D::TopLeft() const { return m_vTopLeft; }
	Vector2 InvertedAABBox2D::BottomRight() const
	{
		return m_vBottomRight;
	}

	double    InvertedAABBox2D::Top() const
	{
		return m_vTopLeft.y;
	}

	double    InvertedAABBox2D::Left() const
	{
		return m_vTopLeft.x;
	}

	double    InvertedAABBox2D::Bottom() const { return m_vBottomRight.y; }
	double    InvertedAABBox2D::Right() const { return m_vBottomRight.x; }
	Vector2 InvertedAABBox2D::Center() const { return m_vCenter; }

	void     InvertedAABBox2D::Render(bool /*RenderCenter*/) const
	{
		/*gdi->Line((int)Left(), (int)Top(), (int)Right(), (int)Top() );
		gdi->Line((int)Left(), (int)Bottom(), (int)Right(), (int)Bottom() );
		gdi->Line((int)Left(), (int)Top(), (int)Left(), (int)Bottom() );
		gdi->Line((int)Right(), (int)Top(), (int)Right(), (int)Bottom() );

		if (RenderCenter)
		{
		  gdi->Circle(m_vCenter, 5);
		}*/
	}
}