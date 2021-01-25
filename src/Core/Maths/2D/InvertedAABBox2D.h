#ifndef INVAABBOX2D_H
#define INVAABBOX2D_H

#include "Maths\Vector2.h"
#include "CA_Export.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	class CA_EXPORT InvertedAABBox2D :
		public AllocatedObject<InvertedAABBox2D>
	{
	private:

		Vector2F  m_vTopLeft;
		Vector2F  m_vBottomRight;

		Vector2F  m_vCenter;

	public:

		InvertedAABBox2D(Vector2F tl, Vector2F br);

		//returns true if the bbox described by other intersects with this one
		bool isOverlappedWith(const InvertedAABBox2D& other)const;

		Vector2F TopLeft()const;
		Vector2F BottomRight()const;

		double    Top() const;
		double    Left() const;
		double    Bottom() const;
		double    Right() const;
		Vector2F  Center() const;

		void     Render(bool RenderCenter = false) const;
	};
}

#endif // INVAABBOX2D_H