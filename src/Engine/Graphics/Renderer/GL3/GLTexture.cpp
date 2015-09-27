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

#include "SystemPlatform.h"

#if CA_PLATFORM_ANDROID

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else

#include <windows.h>

#include <GL/glew.h>
#include <gl/gl.h>
#include "Extensions/glext.h"
#include <gl/glu.h>

#endif // #if CA_PLATFORM_ANDROID

//#include "Graphics/Renderer/GL3/Extensions/glext.h"

#include "GLMacro.h"
#include "GLTexture.h"
#include "GLEnum.h"
#include "GLRenderer.h"
#include "Graphics/PixelUtils.h"
#include "CA_Assert.h"


#include "Log/LogManager.h"


namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Size :        Dimensions de la texture
/// \param Format :      Format de pixel de la texture
/// \param HasMipmaps :  Indique si la texture a des niveaux de mip
/// \param AutoMipmaps : Indique si la texture peut générer ses mips en HW
/// \param Texture :     ID de la texture GL
///
////////////////////////////////////////////////////////////
GLTexture::GLTexture(
	const Vector2I& Size, 
	PixelFormat::TPixelFormat Format, 
	bool HasMipmaps, 
	bool AutoMipmaps, 
	unsigned int Texture,
	const unsigned char *pData_) :
		ITextureBase(Size, Format, HasMipmaps, AutoMipmaps),
		m_Texture   (Texture)
{
	if (pData_ != nullptr)
	{
		m_Data.CopyImage(CImage(Size, Format, pData_));
	}
}


/////////////////////////////////////////////////////////////
/// Destructeur
///
////////////////////////////////////////////////////////////
GLTexture::~GLTexture()
{
    if (m_Texture)
        glDeleteTextures(1, &m_Texture);
}


/////////////////////////////////////////////////////////////
/// Renvoie la texture GL
///
/// \return ID de la texture GL
///
////////////////////////////////////////////////////////////
unsigned int GLTexture::GetGLTexture() const
{
    return m_Texture;
}


/////////////////////////////////////////////////////////////
/// Met à jour les pixels de la texture
///
/// \param Rect : Rectangle à mettre à jour dans la texture
///
////////////////////////////////////////////////////////////
void GLTexture::Update(const CRectangle& Rect)
{
    CA_ASSERT(CRectangle(0, 0, m_Size.x, m_Size.y).Intersects(Rect) != INT_OUT, "GLTexture::Update() : rectangle out of bounds");

	 GLCheck(glBindTexture(GL_TEXTURE_2D, m_Texture));

    GLEnum::TPixelFmt TexFmt = GLEnum::Get(m_Format);
    GLEnum::TPixelFmt ImgFmt = GLEnum::Get(m_Data.GetFormat());

    if (FormatCompressed(m_Data.GetFormat()))
    {
#if CA_PLATFORM_DESKTOP

        // Format de pixel compressé - on utilise une extension pour uploader les pixels
        unsigned long DataSize = Rect.Width() * Rect.Height() * GetBytesPerPixel(m_Data.GetFormat());
        if (Rect.Width() == m_Size.x && Rect.Height() == m_Size.y)
        {
            // Le rectangle source couvre la totalité de l'image : on envoie directement les données
            GLRenderer::glCompressedTexSubImage2DARB(GL_TEXTURE_2D, 0, Rect.Left(), Rect.Top(), Rect.Width(), Rect.Height(), ImgFmt.Format, DataSize, m_Data.GetData());
        }
        else
        {
            // Le rectangle source ne couvre qu'une partie de l'image : on envoie une sous-image de l'image en mémoire
            CImage SubData = m_Data.SubImage(Rect);
            GLRenderer::glCompressedTexSubImage2DARB(GL_TEXTURE_2D, 0, Rect.Left(), Rect.Top(), Rect.Width(), Rect.Height(), ImgFmt.Format, DataSize, SubData.GetData());
        }

#else

		throw NEW_AO CNotImplementedException("GLTexture::Update() : compressed format is not supported\n");

#endif // CA_PLATFORM_DESKTOP

    }
    else
    {
		GLint pixelStore = 0;

		switch (m_Data.GetFormat())
		{
		case PixelFormat::L_8:		///< Luminosity 8 bits (1 byte)
			pixelStore = 1;
			break;

		case PixelFormat::AL_88:		///< Alpha and luminosity 16 bits (2 bytes)
		case PixelFormat::ARGB_1555:	///< RGB 16 bits 1555 (2 bytes)
		case PixelFormat::ARGB_4444:	///< RGB 16 bits 4444 (2 bytes)
		case PixelFormat::PVRTC2:		///< PVR texture compression. Each pixel is 2 bits.
			pixelStore = 2;
			break;

		case PixelFormat::RGB_888:	///< RGB 24 bits 888 (3 bytes)
		case PixelFormat::RGB_DXT1:   ///< S3 DXT1 texture compression (RGB)
			//
		case PixelFormat::ARGB_8888:	///< ARGB 32 bits 8888 (4 bytes)
		case PixelFormat::PVRTC4:	  ///< PVR texture compression. Each pixel is 4 bits.
		case PixelFormat::RGBA_DXT1:  ///< S3 DXT1 texture compression (RGBA)
		case PixelFormat::RGBA_DXT3:  ///< S3 DXT3 texture compression (RGBA)
		case PixelFormat::RGBA_DXT5:  ///< S3 DXT5 texture compression (RGBA)
			pixelStore = 4;
			break;
		}

		GLCheck(glPixelStorei(GL_PACK_ALIGNMENT, pixelStore));

        if (!m_HasMipmaps || m_AutoMipmaps)
        {
            // Pas de mipmap ou génération hardware : on ne met à jour que le premier niveau
            if ((Rect.Width() == m_Size.x) && (Rect.Height() == m_Size.y))
            {
				GLCheck(glTexSubImage2D(GL_TEXTURE_2D, 0,
					0, 0, Rect.Width(), Rect.Height(), ImgFmt.Format, ImgFmt.Type, m_Data.GetData()));
            }
            else
            {
                CImage SubData = m_Data.SubImage(Rect);
				GLCheck(glTexSubImage2D(GL_TEXTURE_2D, 0,
					Rect.Left(), Rect.Top(), Rect.Width(), Rect.Height(), ImgFmt.Format, ImgFmt.Type, SubData.GetData()));
            }
        }
        else
        {

#if CA_PLATFORM_DESKTOP
            // Plusieurs niveaux de mipmapping et génération software : on met à jour tous les niveaux
            GLCheck(gluBuild2DMipmaps(GL_TEXTURE_2D, TexFmt.Internal, m_Size.x, m_Size.y, ImgFmt.Format, ImgFmt.Type, m_Data.GetData()));

#else
			if ((Rect.Width() == m_Size.x) && (Rect.Height() == m_Size.y))
			{
				GLCheck(glTexSubImage2D(GL_TEXTURE_2D, 0,
					0, 0, Rect.Width(), Rect.Height(), ImgFmt.Format, ImgFmt.Type, m_Data.GetData()));
			}
			else
			{
				CImage SubData = m_Data.SubImage(Rect);
				GLCheck(glTexSubImage2D(GL_TEXTURE_2D, 0,
					Rect.Left(), Rect.Top(), Rect.Width(), Rect.Height(), ImgFmt.Format, ImgFmt.Type, SubData.GetData()));
			}

#endif // CA_PLATFORM_DESKTOP

			GLCheck(glGenerateMipmap(GL_TEXTURE_2D));

        }
    }

    GLCheck(glBindTexture(GL_TEXTURE_2D, 0));
}

} // namespace CasaEngine
