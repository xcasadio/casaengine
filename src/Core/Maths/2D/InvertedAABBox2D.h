#ifndef INVAABBOX2D_H
#define INVAABBOX2D_H

#include "Maths/Vector2.h"
#include "CA_Export.h"


namespace CasaEngine
{
	class CA_EXPORT InvertedAABBox2D
	{
	private:
		Vector2  m_vTopLeft;
		Vector2  m_vBottomRight;
		Vector2  m_vCenter;

	public:
		InvertedAABBox2D(Vector2 tl, Vector2 br);

		//returns true if the bbox described by other intersects with this one
		bool isOverlappedWith(const InvertedAABBox2D& other)const;

		Vector2 TopLeft()const;
		Vector2 BottomRight()const;

		double    Top() const;
		double    Left() const;
		double    Bottom() const;
		double    Right() const;
		Vector2  Center() const;

		void     Render(bool RenderCenter = false) const;
	};
}

#endif