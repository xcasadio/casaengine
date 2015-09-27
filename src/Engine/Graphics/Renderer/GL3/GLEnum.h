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

#ifndef GLENUM_H
#define GLENUM_H

#include "SystemPlatform.h"

#if CA_PLATFORM_ANDROID

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else

#include <GL/glew.h>
#include <gl/gl.h>
#include "Extensions/glext.h"

#endif

#include "Graphics/Renderer/Enums.h"

namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    /// Effectue les correspondances entre les enums / flags CasaEngine
    /// et les enums / flags OpenGL
    /////////////////////////////////////////////////////////////
    class GLEnum
    {
    public :

        //----------------------------------------------------------
        // Structure des formats de pixel
        //----------------------------------------------------------
        struct TPixelFmt {GLenum Format, Internal, Type;};

        //----------------------------------------------------------
        // Flags de création de buffer
        //----------------------------------------------------------
        static unsigned long BufferFlags(unsigned long Flags);

        //----------------------------------------------------------
        // Flags de verrouillage
        //----------------------------------------------------------
        static unsigned long LockFlags(unsigned long Flags);

        //----------------------------------------------------------
        // Type des matrices
        //----------------------------------------------------------
        //static GLenum Get(MatrixType::TMatrixType Value);

        //----------------------------------------------------------
        // Formats de pixel
        //----------------------------------------------------------
        static TPixelFmt Get(PixelFormat::TPixelFormat Value);

        //----------------------------------------------------------
        // Paramètres d'alpha-blending
        //----------------------------------------------------------
        static GLenum Get(Blend::TBlend Value);
        
#if CA_PLATFORM_DESKTOP

		//----------------------------------------------------------
		// Opérations sur les unités de texture
		//----------------------------------------------------------
        static GLenum Get(TextureOperation::TTextureOp Value);

        //----------------------------------------------------------
        // Opérateurs des unités de texture
        //----------------------------------------------------------
        static GLenum Get(TTextureArg Value);

#endif // CA_PLATFORM_DESKTOP

        //----------------------------------------------------------
        // Paramètres de rendu
        //----------------------------------------------------------
        static GLenum Get(RenderParameter::TRenderParameter Value);

		/**
		 * Fill Mode
		 */
		static GLenum Get(RenderParameter::TFillMode Value);

		static GLenum Get(TCompareFunction Value);

		static GLenum Get(RenderParameter::TStencilOperation Value);

    private :

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        //static GLenum    MatrixType[];      ///< Types de matrices
        static TPixelFmt PixelFormat[];     ///< Formats de pixel
        static GLenum    Blend[];           ///< Paramètres d'alpha-blending

#if CA_PLATFORM_DESKTOP
        static GLenum    TextureOp[];       ///< Opérateurs de mixage des unités de texture
#endif

        static GLenum    TextureArg[];      ///< Paramètres de mixage des unités de texture
		static GLenum    CompareFunction[];
		static GLenum    StencilOperation[];
        static GLenum    RenderParameter[]; ///< Paramètres de rendu
		static GLenum    FillMode[]; ///< Paramètres de rendu
    };

} // namespace CasaEngine


#endif // GLENUM_H
