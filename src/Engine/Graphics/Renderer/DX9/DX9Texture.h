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

#ifndef DX9TEXTURE_H
#define DX9TEXTURE_H

//==========================================================
// En-têtes
//==========================================================
#include "DX9Renderer.h"
#include "Graphics/Textures/TextureBase.h"
#include "SmartPtr.h"


namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    // Spécialisation DirectX9 des textures
    /////////////////////////////////////////////////////////////
    class DX9Texture : public ITextureBase
    {
    public :

        //----------------------------------------------------------
        // Constructeur
        //----------------------------------------------------------
        DX9Texture(const Vector2I& Size, 
			PixelFormat::TPixelFormat Format, 
			bool HasMipmaps, 
			bool AutoMipmaps, 
			IDirect3DTexture9* Texture,
			const unsigned char *data_ = nullptr);

        //----------------------------------------------------------
        // Renvoie la texture Dx9
        //----------------------------------------------------------
        IDirect3DTexture9* GetDxTexture() const;

    private :

        //----------------------------------------------------------
        // Met à jour les pixels de la texture
        //----------------------------------------------------------
        virtual void Update(const CRectangle& Rect);

        //----------------------------------------------------------
        /// Copie les pixels de la texture sur une surface verrouillée
        //----------------------------------------------------------
        void UpdateSurface(const D3DLOCKED_RECT& LockedRect, const CRectangle& Rect);

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        SmartPtr<IDirect3DTexture9, CResourceCOM> m_Texture; ///< Pointeur sur la texture Dx9
    };

} // namespace CasaEngine


#endif // DX9TEXTURE_H
