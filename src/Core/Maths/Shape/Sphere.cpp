#include  "Sphere.hpp"

namespace CasaEngine
{
	Sphere::Sphere(Vector3 center_, float radius_) :
		IShape(ShapeType::SPHERE), m_Center(center_), m_Radius(radius_)
	{
	}
}