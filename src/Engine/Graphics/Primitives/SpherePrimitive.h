#pragma once

#include "CA_Export.h"

#include "Primitive3D.h"

namespace CasaEngine
{
	class CA_EXPORT SpherePrimitive : public IPrimitive3D
	{
	public:
		SpherePrimitive(float diameter = 1.0f, unsigned int tessellation = 32);
		~SpherePrimitive() override;

	private:
		float _diameter;
		unsigned int _tessellation;
	};
}
