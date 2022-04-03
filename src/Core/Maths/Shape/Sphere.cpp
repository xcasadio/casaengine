#include "Sphere.h"

namespace CasaEngine
{
	Sphere::Sphere(Vector3F center_, float radius_) :
		IShape(SPHERE), m_Center(center_), m_Radius(radius_)
	{
	}
}