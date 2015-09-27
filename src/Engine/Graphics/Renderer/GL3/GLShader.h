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

#ifndef GLSHADER_H
#define GLSHADER_H

#include "SystemPlatform.h"

#if CA_PLATFORM_ANDROID

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else

#include <GL/glew.h>
#include <gl/gl.h>
#include "Extensions/glext.h"

#endif // #if CA_PLATFORM_ANDROID

#include "Graphics/Effects/ShaderBase.h"
#include "Graphics/Textures/TextureBase.h"
#include "IO/IFile.h"


namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    // Spécialisation OpenGL des shaders Cg
    /////////////////////////////////////////////////////////////
    class GLShader : public IShaderBase
    {
    public :

        GLShader(IFile *pFile_);


        /**
         * 
         */
		void Begin();

		/**
         * 
         */
		void End();

		/**
		 * 
		 */
		unsigned int ProgramID() const;

    private :

        //----------------------------------------------------------
        // Change un paramètre (scalaire ou vecteur) du shader
        //----------------------------------------------------------
        virtual void SetParameter(const std::string& Name, const size_t count_, const float* Value);

        //----------------------------------------------------------
        // Change un paramètre (matrice) du shader
        //----------------------------------------------------------
        virtual void SetParameter(const std::string& Name, const Matrix4& Value);

		virtual void SetParameter(const std::string& Name, const ITextureBase* Value);
		
		GLuint m_ProgramID;		
	};

} // namespace CasaEngine


#endif // GLSHADER_H
