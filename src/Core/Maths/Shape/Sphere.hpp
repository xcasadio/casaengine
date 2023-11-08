#ifndef SPHERE_H
#define SPHERE_H

#include "CA_Export.hpp"
#include  "Maths/Vector3.hpp"

#include  "IShape.hpp"

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
