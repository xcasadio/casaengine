#include "Base.h"

#include "CylinderPrimitive.h"
#include "Exceptions.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Graphics/Renderer/Renderer.h"

namespace CasaEngine
{
	Vector3 GetCircleVector(int i_, int tessellation_)
	{
		float angle = i_ * MATH_2PI / tessellation_;

		float dx = cosf(angle);
		float dz = sinf(angle);

		return {dx, 0, dz};
	}

	CylinderPrimitive::CylinderPrimitive(float diameter_, float height_, unsigned int tessellation_) :
		IPrimitive3D(Primitive3DType::CYLINDER)
	{
		m_Diameter = diameter_;
		m_Height = height_;
		m_Tessellation = tessellation_;

		if (m_Tessellation < 3)
		{
			throw ArgumentOutOfRangeException("tessellation");
		}

		m_nbPrimitives = 0;
		Vector3 normal;
		float heightDiv2 = m_Height / 2.0f;
		float radius = m_Diameter / 2;

		for (unsigned int i = 0; i < m_Tessellation; i++)
		{
			normal = GetCircleVector(i, m_Tessellation);
			AddVertex(normal * radius + Vector3::Up() * heightDiv2, normal, Vector2(1.0f, static_cast<float>(i) / static_cast<float>(m_Tessellation)));
			AddVertex(normal * radius + Vector3::Down() * heightDiv2, normal, Vector2(0.0f, static_cast<float>(i) / static_cast<float>(m_Tessellation)));

			AddIndex(i * 2);
			AddIndex(i * 2 + 1);
			AddIndex(i * 2 + 2);

			AddIndex(i * 2 + 1);
			AddIndex(i * 2 + 3);
			AddIndex(i * 2 + 2);

			m_nbPrimitives += 2;
		}

		//last points
		normal = GetCircleVector(m_Tessellation, m_Tessellation);
		AddVertex(normal * radius + Vector3::Up() * heightDiv2, normal, Vector2::One());
		AddVertex(normal * radius + Vector3::Down() * heightDiv2, normal, Vector2(0.0f, 1.0f));

		// Top center
		unsigned int indexTop = this->GetCurrentVertex();
		Vector3 centerTop(0, heightDiv2, 0);
		AddVertex(centerTop, Vector3::Up(), Vector2(0.5f, 0.5f));
		// Bottom center
		unsigned int indexBottom = this->GetCurrentVertex();
		Vector3 centerBottom(0, -heightDiv2, 0);
		AddVertex(centerBottom, Vector3::Down(), Vector2(0.5f, 0.5f));

		for (unsigned int i = 0; i < m_Tessellation; i++)
		{
			normal = GetCircleVector(i, m_Tessellation);
			//TODO : UVs must be compute with a circular way
			AddVertex(normal * radius + Vector3::Up() * heightDiv2, Vector3::Up(), Vector2(1.0f, static_cast<float>(i) / static_cast<float>(m_Tessellation)));
			AddVertex(normal * radius + Vector3::Down() * heightDiv2, Vector3::Down(), Vector2(0.0f, static_cast<float>(i) / static_cast<float>(m_Tessellation)));

			AddIndex(indexTop);
			AddIndex(indexTop + i * 2 + 2);
			AddIndex(indexTop + i * 2 + 4);

			AddIndex(indexBottom);
			AddIndex(indexBottom + i * 2 + 4);
			AddIndex(indexBottom + i * 2 + 2);

			m_nbPrimitives += 2;
		}

		//last points
		normal = GetCircleVector(m_Tessellation, m_Tessellation);
		AddVertex(normal * radius + Vector3::Up() * heightDiv2, Vector3::Up(), Vector2(1.0f, 1.0f));
		AddVertex(normal * radius + Vector3::Down() * heightDiv2, Vector3::Down(), Vector2(0.0f, 1.0f));
	}

	CylinderPrimitive::~CylinderPrimitive()
	{
	}
}