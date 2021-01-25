#ifndef SPHEREPRIMITIVE_H
#define SPHEREPRIMITIVE_H

#include <sstream>
#include <string>
#include <vector>

#include "CA_Export.h"

#include "Graphics/Mesh/Mesh.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Primitive3D.h"

namespace CasaEngine
{
	/**
	 *
	 */
	class CA_EXPORT SpherePrimitive : public IPrimitive3D
	{
	public:
		SpherePrimitive(float diameter_ = 1.0f, unsigned int tessellation_ = 32);
		virtual ~SpherePrimitive();

	private:
		float m_Diameter;
		unsigned int m_Tessellation;
	};
}

#endif // SPHEREPRIMITIVE_H
