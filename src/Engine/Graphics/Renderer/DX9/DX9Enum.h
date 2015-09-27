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

#ifndef DX9ENUM_H
#define DX9ENUM_H

//==========================================================
// En-têtes
//==========================================================
#include <d3d9.h>
#include "Graphics/Renderer/Enums.h"

namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    /// Effectue les correspondances entre les enums / flags CasaEngine
    /// et les enums / flags DirectX9
    /////////////////////////////////////////////////////////////
    class DX9Enum
    {
    public :

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
        //static D3DTRANSFORMSTATETYPE Get(MatrixType::TMatrixType Value);

        //----------------------------------------------------------
        // Type des primitives
        //----------------------------------------------------------
        static D3DPRIMITIVETYPE Get(PrimitiveType::TPrimitiveType Value);

        //----------------------------------------------------------
        // Formats de pixel
        //----------------------------------------------------------
        static D3DFORMAT Get(PixelFormat::TPixelFormat Value);

        //----------------------------------------------------------
        // Paramètres d'alpha-blending
        //----------------------------------------------------------
        static D3DBLEND Get(Blend::TBlend Value);

        //----------------------------------------------------------
        // Opérations sur les unités de texture
        //----------------------------------------------------------
        static D3DTEXTUREOP Get(TextureOperation::TTextureOp Value);

        //----------------------------------------------------------
        // Opérateurs des unités de texture
        //----------------------------------------------------------
        static unsigned long Get(TTextureArg Value);

		//----------------------------------------------------------
		// 
		//----------------------------------------------------------
		static D3DSTENCILOP Get(RenderParameter::TStencilOperation Value);

		//----------------------------------------------------------
		// 
		//----------------------------------------------------------
		static D3DCMPFUNC Get(TCompareFunction Value);

        //----------------------------------------------------------
        // Paramètres de rendu
        //----------------------------------------------------------
        static D3DRENDERSTATETYPE Get(RenderParameter::TRenderParameter Value);

    private :

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        //static D3DTRANSFORMSTATETYPE MatrixType[];      ///< Types de matrices
        static D3DPRIMITIVETYPE      PrimitiveType[];   ///< Types de primitives
        static D3DFORMAT             PixelFormat[];     ///< Formats de pixel
        static D3DBLEND              Blend[];           ///< Paramètres d'alpha-blending
        static D3DTEXTUREOP          TextureOp[];       ///< Opérateurs de mixage des unités de texture
        static unsigned long         TextureArg[];      ///< Paramètres de mixage des unités de texture
		static D3DCMPFUNC			 CompareFunction[]; ///< 
		static D3DSTENCILOP			 StencilOperation[]; ///< 
        static D3DRENDERSTATETYPE    RenderParameter[]; ///< Paramètres de rendu
    };

} // namespace CasaEngine


#endif // DX9ENUM_H
