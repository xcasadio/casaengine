#include  "PlanePrimitive.hpp"
#include  "Maths/Vector3.hpp"
#include  "Maths/Vector2.hpp"

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

		AddVertex((-Vector3::UnitZ() * height_ - Vector3::UnitX() * width_) / 2.0f, Vector3::Up(), Vector2::Zero());
		AddVertex((-Vector3::UnitZ() * height_ + Vector3::UnitX() * width_) / 2.0f, Vector3::Up(), Vector2::UnitX());
		AddVertex((Vector3::UnitZ() * height_ - Vector3::UnitX() * width_) / 2.0f, Vector3::Up(), Vector2::UnitY());
		AddVertex((Vector3::UnitZ() * height_ + Vector3::UnitX() * width_) / 2.0f, Vector3::Up(), Vector2::One());

		m_nbPrimitives = 2;
	}
}