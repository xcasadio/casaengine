#pragma once

#include "CA_Export.hpp"

#include  "Primitive3D.hpp"

namespace CasaEngine
{
	class CA_EXPORT CylinderPrimitive : public IPrimitive3D
	{
	public:
		CylinderPrimitive(float diameter_ = 1.0f, float height_ = 1.0f, unsigned int tessellation_ = 32);
		~CylinderPrimitive() override;

	private:
		float m_Diameter;
		float m_Height;
		unsigned int m_Tessellation;
	};
}