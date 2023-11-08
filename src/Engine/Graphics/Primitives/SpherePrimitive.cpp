#include  "Base.hpp"

#include  "SpherePrimitive.hpp"
#include  "Exceptions.hpp"
#include  "Maths/Vector3.hpp"
#include  "Maths/Vector2.hpp"
#include  "Graphics/Renderer/Renderer.hpp"

namespace CasaEngine
{
	SpherePrimitive::SpherePrimitive(const float diameter, unsigned int tessellation) :
		IPrimitive3D(Primitive3DType::SPHERE)
	{
		if (tessellation < 3)
		{
			throw new ArgumentOutOfRangeException("tessellation < 3");
		}

		int verticalSegments = tessellation;
		int horizontalSegments = tessellation * 2;

		_diameter = diameter;
		_tessellation = tessellation;
		float radius = diameter / 2.0f;

		//TODO : UVs are not the same with OpenGL and DX

		// Create rings of vertices at progressively higher latitudes.
		for (int i = 0; i <= verticalSegments; i++)
		{
			float latitude = static_cast<float>(i) * Math::Pi / static_cast<float>(verticalSegments) - Math::PI_OVER_2;
			float dy = sinf(latitude);
			float dxz = cosf(latitude);

			// Create a single ring of vertices at this latitude.
			for (int j = 0; j <= horizontalSegments; j++)
			{
				float longitude = static_cast<float>(j) * Math::MATH_2PI / static_cast<float>(horizontalSegments);

				float dx = cosf(longitude) * dxz;
				float dz = sinf(longitude) * dxz;

				Vector3 normal(dx, dy, dz);
				AddVertex(normal * radius, normal, Vector2(static_cast<float>(j) / static_cast<float>(horizontalSegments), static_cast<float>(i) / static_cast<float>(verticalSegments)));
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

	SpherePrimitive::~SpherePrimitive() = default;
}
