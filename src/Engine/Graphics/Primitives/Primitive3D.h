#ifndef PRIMITIVE3D_H
#define PRIMITIVE3D_H

#include "CA_Export.h"

#include <vector>

#include "Graphics/Mesh/Mesh.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	class CA_EXPORT IPrimitive3D :
		public AllocatedObject<IPrimitive3D>
	{
	public:
		/**
		 *
		 */
		enum Primitive3DType
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

		Mesh* CreateModel();

	protected:
		IPrimitive3D(Primitive3DType type_);

		/**
		 * Adds a new vertex to the primitive model. This should only be called
		 * during the initialization process, before InitializePrimitive.
		 */
		void AddVertex(Vector3F position, Vector3F normal, Vector2F UV_);

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

#endif // PRIMITIVE3D_H
