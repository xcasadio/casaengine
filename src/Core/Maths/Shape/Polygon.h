#pragma once

#include "CA_Export.h"
#include "IShape.h"
#include "Maths/Vector2.h"

#include <vector>

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
