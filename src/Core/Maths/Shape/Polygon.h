#ifndef POLYGON_H
#define POLYGON_H

#include "CA_Export.h"

#include "IShape.h"
#include "Maths/Vector2.h"

namespace CasaEngine
{
	class CA_EXPORT Polygon : public IShape
	{
	public:
		Polygon();

	private:
		std::vector<Vector2> m_PointList;
	};
}

#endif
