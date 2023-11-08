#pragma once

#include "CA_Export.hpp"
#include  "IShape.hpp"
#include  "Maths/Vector2.hpp"

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
