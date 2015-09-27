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

#ifndef GLBUFFER_H
#define GLBUFFER_H

#include "SystemPlatform.h"

#if CA_PLATFORM_ANDROID

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else

#include <GL/glew.h>
#include <gl/gl.h>
#include "Extensions/glext.h"

#endif // #if CA_PLATFORM_ANDROID

#include "GLRenderer.h"
#include "Graphics/Vertices/BufferBase.h"
#include "GLEnum.h"
#include "GLMacro.h"

#include "Log\LogManager.h"
#include "Log\LogVerbose.h"

namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    /// Spécialisation OpenGL des vertex / index buffers
    /////////////////////////////////////////////////////////////
    template <int Type>
    class GLBuffer : public IBufferBase
    {
    public :

        //----------------------------------------------------------
        // Constructeur
        //----------------------------------------------------------
        GLBuffer(unsigned long Count, unsigned int Buffer);

        //----------------------------------------------------------
        // Destructeur
        //----------------------------------------------------------
        virtual ~GLBuffer();

        //----------------------------------------------------------
        // Renvoie un poiteur sur le buffer
        //----------------------------------------------------------
        unsigned int GetBuffer() const;

    private :

		/**
		 * 
		 */
		void Fill(const void* Data, unsigned long size_, unsigned long flags_);

        //----------------------------------------------------------
        // Verrouille le buffer
        //----------------------------------------------------------
        void* Lock(unsigned long Offset, unsigned long Size, unsigned long Flags);

        //----------------------------------------------------------
        // Déverouille le buffer
        //----------------------------------------------------------
        void Unlock();

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        unsigned int m_Buffer; ///< Identifiant du buffer GL
    };

	//	GL_ARRAY_BUFFER
	//	GL_ATOMIC_COUNTER_BUFFER
	//	GL_COPY_READ_BUFFER
	//	GL_COPY_WRITE_BUFFER
	//	GL_DRAW_INDIRECT_BUFFER
	//	GL_DISPATCH_INDIRECT_BUFFER
	//	GL_ELEMENT_ARRAY_BUFFER
	//	GL_PIXEL_PACK_BUFFER
	//	GL_PIXEL_UNPACK_BUFFER
	//	GL_QUERY_BUFFER
	//	GL_SHADER_STORAGE_BUFFER
	//	GL_TEXTURE_BUFFER
	//	GL_TRANSFORM_FEEDBACK_BUFFER
	//	GL_UNIFORM_BUFFER

    #if CA_PLATFORM_ANDROID

    typedef GLBuffer<GL_ARRAY_BUFFER>         GLVertexBuffer;
    typedef GLBuffer<GL_ELEMENT_ARRAY_BUFFER> GLIndexBuffer;

	#else

	typedef GLBuffer<GL_ARRAY_BUFFER_ARB>         GLVertexBuffer;
	typedef GLBuffer<GL_ELEMENT_ARRAY_BUFFER_ARB> GLIndexBuffer;

	#endif // #if CA_PLATFORM_ANDROID

    #include "GLBuffer.inl"

} // namespace CasaEngine


#endif // GLBUFFER_H
