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

#ifndef GLTEXTURE_H
#define GLTEXTURE_H

//==========================================================
// En-têtes
//==========================================================
#include "Graphics/Textures/TextureBase.h"


namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    /// Spécialisation OpenGL des textures
    /////////////////////////////////////////////////////////////
    class GLTexture : public ITextureBase
    {
    public :

        //----------------------------------------------------------
        // Constructeur
        //----------------------------------------------------------
		GLTexture(
			const Vector2I& Size, 
			PixelFormat::TPixelFormat Format, 
			bool HasMipmaps, 
			bool AutoMipmaps, 
			unsigned int Texture,
			const unsigned char *pData_ = nullptr);

        //----------------------------------------------------------
        // Destructeur
        //----------------------------------------------------------
        ~GLTexture();

        //----------------------------------------------------------
        // Renvoie la texture GL
        //----------------------------------------------------------
        unsigned int GetGLTexture() const;

    private :

        //----------------------------------------------------------
        // Met à jour les pixels de la texture
        //----------------------------------------------------------
        virtual void Update(const CRectangle& Rect);

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        unsigned int m_Texture; ///< Identifiant GL de la texture
    };

} // namespace CasaEngine


#endif // GLTEXTURE_H
