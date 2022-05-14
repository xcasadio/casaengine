#include "Base.h"

#include "TorusPrimitive.h"
#include "Exceptions.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Graphics/Renderer/Renderer.h"
#include "Maths/Matrix4.h"

namespace CasaEngine
{
	/**
	 *
	 */
	TorusPrimitive::TorusPrimitive(float diameter_, float thickness_, unsigned int tessellation_) :
		IPrimitive3D(Primitive3DType::TORUS)
	{
		m_Diameter = diameter_;
		m_Thickness = thickness_;
		m_Tessellation = tessellation_;

		//TODO : UVs are not the same with OpenGL and DX

		if (tessellation_ < 3)
			throw new ArgumentOutOfRangeException("tessellation");

		m_nbPrimitives = 0;

		// First we loop around the main ring of the torus.
		for (unsigned int i = 0; i < m_Tessellation; i++)
		{
			float outerAngle = static_cast<float>(i) * MATH_2PI / static_cast<float>(m_Tessellation);

			// Create a transform matrix that will align geometry to
			// slice perpendicularly though the current ring position.
			/*Matrix4 transform, matRot;
			transform.CreateTranslation(m_Diameter / 2.0f, 0, 0);
			matRot.CreateRotationY(outerAngle);
			transform *= matRot;*/
			Matrix4 transform;
			transform.CreateRotationY(outerAngle);
			transform.Translation(m_Diameter / 2.0f, 0, 0);

			int step = m_Tessellation + 1;

			// Now we loop along the other axis, around the side of the tube.
			for (unsigned int j = 0; j <= m_Tessellation; j++)
			{
				float innerAngle = static_cast<float>(j) * MATH_2PI / static_cast<float>(m_Tessellation);

				float dx = cosf(innerAngle);
				float dy = sinf(innerAngle);

				// Create a vertex.
				Vector3 normal(dx, dy, 0);
				Vector3 position = normal * m_Thickness / 2.0f;

				position = transform.Transform(position);
				transform.TransformNormal(normal, normal);

				AddVertex(position, normal, Vector2(static_cast<float>(i) / static_cast<float>(m_Tessellation), static_cast<float>(j) / static_cast<float>(m_Tessellation)));

				// And create indices for two triangles.
				int nextI = (i + 1) % step;
				int nextJ = (j + 1) % step;

				AddIndex(i * step + j);
				AddIndex(i * step + nextJ);
				AddIndex(nextI * step + j);

				AddIndex(i * step + nextJ);
				AddIndex(nextI * step + nextJ);
				AddIndex(nextI * step + j);

				m_nbPrimitives += 2;
			}
		}
	}

	/**
	 *
	 */
	TorusPrimitive::~TorusPrimitive()
	{
	}
}