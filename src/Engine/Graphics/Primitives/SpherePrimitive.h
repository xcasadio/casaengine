#pragma once

#include "CA_Export.h"

#include "Primitive3D.h"

namespace CasaEngine
{
	class CA_EXPORT SpherePrimitive : public IPrimitive3D
	{
	public:
		SpherePrimitive(float diameter_ = 1.0f, unsigned int tessellation_ = 32);
		~SpherePrimitive() override;

	private:
		float m_Diameter;
		unsigned int m_Tessellation;
	};
}
