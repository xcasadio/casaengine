#ifndef POLYGON_H
#define POLYGON_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"

#include "IShape.h"
#include "Maths/Vector2.h"

namespace CasaEngine
{
	class CA_EXPORT Polygon :
		public IShape, public virtual AllocatedObject<Polygon>
	{
	public:
		Polygon();
		~Polygon();

	private:
		std::vector<Vector2F> m_PointList;
	};
}

#endif // POLYGON_H
