#pragma once

#include "CA_Export.hpp"

#include  "Primitive3D.hpp"

namespace CasaEngine
{
	class CA_EXPORT TorusPrimitive : public IPrimitive3D
	{
	public:
		TorusPrimitive(float diameter_ = 1.0f, float thickness_ = 0.333f, unsigned int tessellation_ = 32);
		~TorusPrimitive() override;

	private:
		float m_Diameter;
		float m_Thickness;
		unsigned int m_Tessellation;
	};
}
