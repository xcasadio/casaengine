#pragma once

#include "CA_Export.hpp"

#include  "Primitive3D.hpp"

namespace CasaEngine
{
	class CA_EXPORT PlanePrimitive : public IPrimitive3D
	{
	public:
		PlanePrimitive(float width_ = 1.0f, float height_ = 1.0f);

	private:
		float m_Width;
		float m_Height;
	};
}
