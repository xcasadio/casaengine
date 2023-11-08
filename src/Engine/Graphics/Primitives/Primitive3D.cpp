#include  "Base.hpp"

#include  "Primitive3D.hpp"
#include  "Maths/Vector3.hpp"
#include  "Maths/Vector2.hpp"
#include  "Graphics/Renderer/Renderer.hpp"
#include  "Graphics/Mesh/Mesh.hpp"

namespace CasaEngine
{
	IPrimitive3D::IPrimitive3D(Primitive3DType type_) :
		m_PrimitiveType(type_)
	{
	}

	IPrimitive3D::~IPrimitive3D()
		= default;

	/// <summary>
	/// Adds a new vertex to the primitive model. This should only be called
	/// during the initialization process, before InitializePrimitive.
	/// </summary>
	void IPrimitive3D::AddVertex(Vector3 position, Vector3 normal, Vector2 UV_)
	{
		VertexPositionNormalTexture v;
		v.Position = position;
		v.Normal = normal;
		v.TexCoords = UV_;

		m_Vertices.push_back(v);
	}

	/// <summary>
	/// Adds a new index to the primitive model. This should only be called
	/// during the initialization process, before InitializePrimitive.
	/// </summary>
	void IPrimitive3D::AddIndex(unsigned int index)
	{
		m_Indices.push_back(static_cast<short>(index));
	}

	/// <summary>
	/// Queries the index of the current vertex. This starts at
	/// zero, and increments every time AddVertex is called.
	/// </summary>
	unsigned int IPrimitive3D::GetCurrentVertex()
	{
		return static_cast<unsigned>(m_Vertices.size());
	}

	/**
	 * The new Mesh must be deleted
	 */
	Mesh* IPrimitive3D::CreateMesh()
	{
		return new Mesh(m_Vertices.data(), m_Vertices.size(), m_Indices.data(), m_Indices.size());
	}
}