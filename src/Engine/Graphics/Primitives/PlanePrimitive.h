#ifndef PLANEPRIMITIVE_H
#define PLANEPRIMITIVE_H

#include "CA_Export.h"

#include "Primitive3D.h"

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

#endif
