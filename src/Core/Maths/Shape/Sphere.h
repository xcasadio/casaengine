#ifndef SPHERE_H
#define SPHERE_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"

#include "IShape.h"

namespace CasaEngine
{
	class CA_EXPORT Sphere :
		public IShape, public virtual AllocatedObject<Sphere>
	{
	public:
		Sphere(Vector3F center_, float radius_);
		~Sphere();

	private:
		Vector3F m_Center;
		float m_Radius;
	};
}

#endif // SPHERE_H
