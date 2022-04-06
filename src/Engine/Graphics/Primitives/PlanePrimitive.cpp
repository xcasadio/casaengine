#include "PlanePrimitive.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"

namespace CasaEngine
{
	PlanePrimitive::PlanePrimitive(float width_, float height_) :
		IPrimitive3D(Primitive3DType::PLANE), m_Width(width_), m_Height(height_)
	{
		//TODO : UVs are not the same with OpenGL and DX

		AddIndex(GetCurrentVertex() + 0);
		AddIndex(GetCurrentVertex() + 1);
		AddIndex(GetCurrentVertex() + 2);
		
		AddIndex(GetCurrentVertex() + 1);
		AddIndex(GetCurrentVertex() + 3);
		AddIndex(GetCurrentVertex() + 2);

		AddVertex((-Vector3F::UnitZ() * height_ - Vector3F::UnitX() * width_) / 2.0f, Vector3F::Up(), Vector2F::Zero());
		AddVertex((-Vector3F::UnitZ() * height_ + Vector3F::UnitX() * width_) / 2.0f, Vector3F::Up(), Vector2F::UnitX());
		AddVertex((Vector3F::UnitZ() * height_ - Vector3F::UnitX() * width_) / 2.0f, Vector3F::Up(), Vector2F::UnitY());
		AddVertex((Vector3F::UnitZ() * height_ + Vector3F::UnitX() * width_) / 2.0f, Vector3F::Up(), Vector2F::One());

		m_nbPrimitives = 2;
	}
}