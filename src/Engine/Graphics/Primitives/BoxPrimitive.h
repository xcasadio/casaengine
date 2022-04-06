#ifndef BOXPRIMITIVE_H
#define BOXPRIMITIVE_H

#include "CA_Export.h"

#include "Primitive3D.h"

namespace CasaEngine
{
	class CA_EXPORT BoxPrimitive : public IPrimitive3D
	{
	public:
		BoxPrimitive(float width_ = 1.0f, float height_ = 1.0f, float length_ = 1.0f);
		virtual ~BoxPrimitive();

	private:
		void AddIndex(bool dir_);

	private:
		float m_Width;
		float m_Height;
		float m_Length;
	};
}

#endif
