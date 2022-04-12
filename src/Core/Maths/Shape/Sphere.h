#ifndef SPHERE_H
#define SPHERE_H

#include "CA_Export.h"
#include "Maths/Vector3.h"

#include "IShape.h"

namespace CasaEngine
{
	class CA_EXPORT Sphere : public IShape
	{
	public:
		Sphere(Vector3 center_, float radius_);

	private:
		Vector3 m_Center;
		float m_Radius;
	};
}

#endif
