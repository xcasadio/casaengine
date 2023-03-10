#pragma once

#include "CA_Export.h"

#include <vector>

#include "Graphics/Mesh/Mesh.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"

namespace CasaEngine
{
	class CA_EXPORT IPrimitive3D
	{
	public:
		enum class Primitive3DType
		{
			BOX,
			SPHERE,
			PLANE,
			CYLINDER,
			TORUS,
			//TEAPOT,
			//BEZIER_CURVE
		};

	public:
		virtual ~IPrimitive3D();

		Mesh* CreateMesh();

	protected:
		IPrimitive3D(Primitive3DType type_);

		/**
		 * Adds a new vertex to the primitive model. This should only be called
		 * during the initialization process, before InitializePrimitive.
		 */
		void AddVertex(Vector3 position, Vector3 normal, Vector2 UV_);

		/**
		 * Adds a new index to the primitive model. This should only be called
		 * during the initialization process, before InitializePrimitive.
		 */
		void AddIndex(unsigned int index);

		/**
		 * Queries the index of the current vertex. This starts at
		 * zero, and increments every time AddVertex is called.
		 */
		unsigned int GetCurrentVertex();

	protected:
		unsigned int m_nbPrimitives;

	private:
		Primitive3DType m_PrimitiveType;
		std::vector<VertexPositionNormalTexture> m_Vertices;
		std::vector<unsigned short> m_Indices;
	};
}
