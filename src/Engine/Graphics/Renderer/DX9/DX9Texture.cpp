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


//==========================================================
// En-têtes
//==========================================================
#include "DX9Texture.h"
#include "DX9Enum.h"
#include "DX9Exception.h"
#include "Graphics/PixelUtils.h"


#include "DX9Macro.h"
#include "Macro.h"
#include "CA_Assert.h"


namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Size :        Dimensions de la texture
/// \param Format :      Format de pixel de la texture
/// \param HasMipmaps :  Indique si la texture a des niveaux de mip
/// \param AutoMipmaps : Indique si la texture peut générer ses mips en HW
/// \param Texture :     ID de la texture Dx
///
////////////////////////////////////////////////////////////
DX9Texture::DX9Texture(
	const Vector2I& Size, 
	PixelFormat::TPixelFormat Format, 
	bool HasMipmaps, 
	bool AutoMipmaps, 
	IDirect3DTexture9* Texture,
	const unsigned char* pData_) :
		ITextureBase(Size, Format, HasMipmaps, AutoMipmaps),
		m_Texture(Texture)
{
	if (pData_ != nullptr)
	{
		m_Data.CopyImage(CImage(Size, Format, pData_));
		Update(CRectangle(0, 0, Size.x, Size.y));
	}
}


/////////////////////////////////////////////////////////////
/// Renvoie la texture Dx9
///
/// \return Pointeur sur la texture Dx9
///
////////////////////////////////////////////////////////////
IDirect3DTexture9* DX9Texture::GetDxTexture() const
{
    return m_Texture;
}


/////////////////////////////////////////////////////////////
/// Met à jour les pixels de la texture
///
/// \param Rect : Rectangle à mettre à jour dans la texture
///
////////////////////////////////////////////////////////////
void DX9Texture::Update(const CRectangle& Rect)
{
    CA_ASSERT(CRectangle(0, 0, m_Size.x, m_Size.y).Intersects(Rect) == INT_IN, "DX9Texture::Update() : rectangle out of bounds");

    // Si le format des pixels à copier est le même que celui de la texture on fait une simple copie,
	// sinon on effectue une conversion
    if (m_Format == m_Data.GetFormat())
    {
        // Verrouillage de la texture
        D3DLOCKED_RECT LockedRect;
        RECT Lock = {Rect.Left(), Rect.Top(), Rect.Right(), Rect.Bottom()};
        DXCheck(m_Texture->LockRect(0, &LockedRect, &Lock, 0));

        // Copie des pixels
        UpdateSurface(LockedRect, Rect);

        // Déverrouillage de la texture
        m_Texture->UnlockRect(0);
    }
    else
    {
        // Récupération du device
        SmartPtr<IDirect3DDevice9, CResourceCOM> Device;
        m_Texture->GetDevice(&GetPtr(Device));

        // Création d'une texture en mémoire système pour y copier les pixels
        SmartPtr<IDirect3DSurface9, CResourceCOM> Src;
        if (FAILED(Device->CreateOffscreenPlainSurface(Rect.Width(), Rect.Height(), DX9Enum::Get(m_Data.GetFormat()), D3DPOOL_SYSTEMMEM, &GetPtr(Src), nullptr)))
            throw DX9Exception("CreateOffscreenPlainSurface", "DX9Texture::Update");

        // Verrouillage de la texture temporaire
        D3DLOCKED_RECT LockedRect;
        Src->LockRect(&LockedRect, nullptr, 0);

        // Copie des pixels
        UpdateSurface(LockedRect, Rect);

        // Déverrouillage de la texture temporaire
        Src->UnlockRect();

        // Récupération de la surface de niveau 0 de la texture
        SmartPtr<IDirect3DSurface9, CResourceCOM> Dest;
        m_Texture->GetSurfaceLevel(0, &GetPtr(Dest));

        // Copie de la surface Src sur la surface Dest (c'est ici qu'est effectuée la conversion de format)
        RECT DestRect = {Rect.Left(), Rect.Top(), Rect.Right(), Rect.Bottom()};
        if (FAILED(D3DXLoadSurfaceFromSurface(Dest, nullptr, &DestRect, Src, nullptr, nullptr, D3DX_DEFAULT, 0)))
            throw DX9Exception("D3DXLoadSurfaceFromSurface", "DX9Texture::Update");
    }

    // Génération des niveaux de mipmapping si nécessaire
    if (m_HasMipmaps)
    {
        if (m_AutoMipmaps)
            m_Texture->GenerateMipSubLevels();
        else
            D3DXFilterTexture(m_Texture, nullptr, D3DX_DEFAULT, D3DX_DEFAULT);
    }
}


////////////////////////////////////////////////////////////
/// Copie les pixels de la texture sur une surface verrouillée
///
/// \param LockedRect : Structure contenant les infos de verrouillage
/// \param Rect :       Rectangle source à copier
///
////////////////////////////////////////////////////////////
void DX9Texture::UpdateSurface(const D3DLOCKED_RECT& LockedRect, const CRectangle& Rect)
{
    // Récupération d'un pointeur sur les pixels source et destination
    unsigned char* DestPix = reinterpret_cast<unsigned char*>(LockedRect.pBits);
    const unsigned char* SrcPix = m_Data.GetData() + (Rect.Left() + Rect.Top() * m_Size.x) * GetBytesPerPixel(m_Data.GetFormat());

    // Copie des pixels sur la surface
    unsigned int Bpp = GetBytesPerPixel(m_Data.GetFormat());
    for (int i = 0; i < Rect.Height(); ++i)
    {
		std::copy(SrcPix, SrcPix + Rect.Width() * Bpp, DestPix);
        SrcPix  += m_Size.x * Bpp;
        DestPix += LockedRect.Pitch;
    }
}

} // namespace CasaEngine
