#include "Base.h"

#include "SpherePrimitive.h"
#include "Exceptions.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Graphics/Renderer/Renderer.h"

namespace CasaEngine
{
	/**
	 *
	 */
	SpherePrimitive::SpherePrimitive(float diameter_, unsigned int tessellation_) :
		IPrimitive3D(SPHERE)
	{
		if (tessellation_ < 3)
			throw NEW_AO CArgumentOutOfRangeException("tessellation < 3");

		int verticalSegments = tessellation_;
		int horizontalSegments = tessellation_ * 2;

		m_Diameter = diameter_;
		m_Tessellation = tessellation_;
		float radius = diameter_ / 2.0f;

		//TODO : UVs are not the same with OpenGL and DX

		// Create rings of vertices at progressively higher latitudes.
		for (int i = 0; i <= verticalSegments; i++)
		{
			float latitude = static_cast<float>(i) * Pi /
				static_cast<float>(verticalSegments) - MATH_PI_DIV_2;

			float dy = sinf(latitude);
			float dxz = cosf(latitude);

			// Create a single ring of vertices at this latitude.
			for (int j = 0; j <= horizontalSegments; j++)
			{
				float longitude = static_cast<float>(j) * MATH_2PI / static_cast<float>(horizontalSegments);

				float dx = static_cast<float>(cosf(longitude)) * dxz;
				float dz = static_cast<float>(sinf(longitude)) * dxz;

				Vector3F normal(dx, dy, dz);
				AddVertex(normal * radius, normal, Vector2F(static_cast<float>(j) / static_cast<float>(horizontalSegments), static_cast<float>(i) / static_cast<float>(verticalSegments)));
			}
		}

		// Fill the sphere body with triangles joining each pair of latitude rings.
		m_nbPrimitives = 0;
		int horizontalStep = horizontalSegments + 1;

		for (int i = 0; i < verticalSegments; i++)
		{
			for (int j = 0; j < horizontalSegments; j++)
			{
				int nextI = i + 1;
				int nextJ = (j + 1) % horizontalStep;

				AddIndex(i * horizontalStep + j);
				AddIndex(i * horizontalStep + nextJ);
				AddIndex(nextI * horizontalStep + j);

				AddIndex(i * horizontalStep + nextJ);
				AddIndex(nextI * horizontalStep + nextJ);
				AddIndex(nextI * horizontalStep + j);

				m_nbPrimitives += 2;
			}
		}
	}

	/**
	 *
	 */
	SpherePrimitive::~SpherePrimitive()
	{
	}
}