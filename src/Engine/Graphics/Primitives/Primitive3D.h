//==========================================================
// CasaEngine - Free C++ 3D engine
//
// Copyright (C) 2004-2005 Laurent Gomila
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
// E-mail : laurent.gom@gmail.com
//==========================================================

#ifndef PRIMITIVE3D_H
#define PRIMITIVE3D_H

//==========================================================
// En-têtes
//==========================================================

#include "CA_Export.h"

#include <sstream>
#include <string>
#include <vector>

#include "Graphics/Mesh/Mesh.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Classe de base abstraite pour les loggers
    ////////////////////////////////////////////////////////////
    class CA_EXPORT IPrimitive3D :
		public AllocatedObject<IPrimitive3D>
    {
	public :
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

    public :		     
        virtual ~IPrimitive3D();

		Mesh *CreateModel();

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

} // namespace CasaEngine

#endif // PRIMITIVE3D_H
