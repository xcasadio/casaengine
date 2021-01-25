//==========================================================
// CasaEngine - Free C++ 3D engine
//
// Copyright (C) 2013-2014 Xavier Casadio
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc.,
// 59 Temple Place - Suite 330,
// Boston, MA  02111-1307, USA.
//
// E-mail : casaprod@gmail.com
//==========================================================

//==========================================================
// En-têtes
//==========================================================
#include "Base.h"

#include "Primitive3D.h"
#include "Exceptions.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Mesh/Mesh.h"
#include "Log/LogManager.h"
#include "Log/LogVerbose.h"

namespace CasaEngine
{
	/**
	 *
	 */
	IPrimitive3D::IPrimitive3D(Primitive3DType type_) :
		m_PrimitiveType(type_)
	{
	}

	/**
		*
		*/
	IPrimitive3D::~IPrimitive3D()
	{
	}

	/// <summary>
	/// Adds a new vertex to the primitive model. This should only be called
	/// during the initialization process, before InitializePrimitive.
	/// </summary>
	void IPrimitive3D::AddVertex(Vector3F position, Vector3F normal, Vector2F UV_)
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
		return m_Vertices.size();
	}

	/**
	 * The new Mesh must be deleted
	 */
	Mesh* IPrimitive3D::CreateModel()
	{
		return NEW_AO Mesh(m_Vertices.data(), m_Vertices.size(), m_Indices.data(), m_Indices.size());
	}
}