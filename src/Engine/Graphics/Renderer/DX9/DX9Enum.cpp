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
#include "DX9Enum.h"


namespace CasaEngine
{

////////////////////////////////////////////////////////////
// Tables de correspondance
////////////////////////////////////////////////////////////
/*D3DTRANSFORMSTATETYPE DX9Enum::MatrixType[] =
{
    D3DTS_WORLD,
    D3DTS_PROJECTION,
    D3DTS_TEXTURE0,
    D3DTS_TEXTURE1,
    D3DTS_TEXTURE2,
    D3DTS_TEXTURE3
};*/
D3DPRIMITIVETYPE DX9Enum::PrimitiveType[] =
{
    D3DPT_TRIANGLELIST,
    D3DPT_TRIANGLESTRIP,
    D3DPT_TRIANGLEFAN,
    D3DPT_LINELIST,
    D3DPT_LINESTRIP,
    D3DPT_POINTLIST
};
D3DFORMAT DX9Enum::PixelFormat[] =
{
	D3DFMT_L8,
	D3DFMT_A8L8,
	D3DFMT_A1R5G5B5,
	D3DFMT_A4R4G4B4,
	D3DFMT_R8G8B8,
	D3DFMT_A8R8G8B8,
    D3DFMT_DXT1,
    D3DFMT_DXT3,
    D3DFMT_DXT5
};
D3DBLEND DX9Enum::Blend[] =
{
    D3DBLEND_SRCALPHA,
    D3DBLEND_INVSRCALPHA,
    D3DBLEND_DESTALPHA,
    D3DBLEND_INVDESTALPHA,
    D3DBLEND_SRCCOLOR,
    D3DBLEND_INVSRCCOLOR,
    D3DBLEND_DESTCOLOR,
    D3DBLEND_INVDESTCOLOR,
    D3DBLEND_ONE,
    D3DBLEND_ZERO
};
D3DTEXTUREOP DX9Enum::TextureOp[] =
{
    D3DTOP_SELECTARG1,
    D3DTOP_ADD,
    D3DTOP_MODULATE,
    D3DTOP_SELECTARG1,
    D3DTOP_ADD,
    D3DTOP_MODULATE
};
unsigned long DX9Enum::TextureArg[] =
{
    D3DTA_DIFFUSE,
    D3DTA_TEXTURE,
    D3DTA_CURRENT,
    D3DTA_TFACTOR
};
D3DCMPFUNC DX9Enum::CompareFunction[] =
{
	D3DCMP_ALWAYS,
	D3DCMP_NEVER,
	D3DCMP_LESS,	
	D3DCMP_LESSEQUAL,
	D3DCMP_EQUAL,
	D3DCMP_GREATEREQUAL,
	D3DCMP_GREATER,
	D3DCMP_NOTEQUAL
};

D3DSTENCILOP DX9Enum::StencilOperation[] =
{
	D3DSTENCILOP_KEEP,
	D3DSTENCILOP_ZERO,
	D3DSTENCILOP_REPLACE,
	D3DSTENCILOP_INCR,
	D3DSTENCILOP_DECR,
	D3DSTENCILOP_INCRSAT,
	D3DSTENCILOP_DECRSAT,
	D3DSTENCILOP_INVERT
};
D3DRENDERSTATETYPE DX9Enum::RenderParameter[] =
{
	D3DRS_ZENABLE,
    D3DRS_ZWRITEENABLE,
    D3DRS_ALPHABLENDENABLE,
	D3DRS_CULLMODE,
	D3DRS_FILLMODE,
	D3DRS_SCISSORTESTENABLE,
	D3DRS_STENCILENABLE,   
	D3DRS_STENCILFAIL,     
	D3DRS_STENCILZFAIL,    
	D3DRS_STENCILPASS,     
	D3DRS_STENCILFUNC,     
	D3DRS_STENCILREF,      
	D3DRS_STENCILMASK,     
	D3DRS_STENCILWRITEMASK,

	/*D3DRS_TWOSIDEDSTENCILMODE,
	D3DRS_CCW_STENCILFAIL,
	D3DRS_CCW_STENCILZFAIL,
	D3DRS_CCW_STENCILPASS,
	D3DRS_CCW_STENCILFUNC*/

};


/*
D3DRS_ZENABLE                     = 7,
D3DRS_FILLMODE                    = 8,
D3DRS_SHADEMODE                   = 9,
D3DRS_ZWRITEENABLE                = 14,
D3DRS_ALPHATESTENABLE             = 15,
D3DRS_LASTPIXEL                   = 16,
D3DRS_SRCBLEND                    = 19,
D3DRS_DESTBLEND                   = 20,
D3DRS_CULLMODE                    = 22,
D3DRS_ZFUNC                       = 23,
D3DRS_ALPHAREF                    = 24,
D3DRS_ALPHAFUNC                   = 25,
D3DRS_DITHERENABLE                = 26,
D3DRS_ALPHABLENDENABLE            = 27,
D3DRS_FOGENABLE                   = 28,
D3DRS_SPECULARENABLE              = 29,
D3DRS_FOGCOLOR                    = 34,
D3DRS_FOGTABLEMODE                = 35,
D3DRS_FOGSTART                    = 36,
D3DRS_FOGEND                      = 37,
D3DRS_FOGDENSITY                  = 38,
D3DRS_RANGEFOGENABLE              = 48,
D3DRS_STENCILENABLE               = 52,
D3DRS_STENCILFAIL                 = 53,
D3DRS_STENCILZFAIL                = 54,
D3DRS_STENCILPASS                 = 55,
D3DRS_STENCILFUNC                 = 56,
D3DRS_STENCILREF                  = 57,
D3DRS_STENCILMASK                 = 58,
D3DRS_STENCILWRITEMASK            = 59,
D3DRS_TEXTUREFACTOR               = 60,
D3DRS_WRAP0                       = 128,
D3DRS_WRAP1                       = 129,
D3DRS_WRAP2                       = 130,
D3DRS_WRAP3                       = 131,
D3DRS_WRAP4                       = 132,
D3DRS_WRAP5                       = 133,
D3DRS_WRAP6                       = 134,
D3DRS_WRAP7                       = 135,
D3DRS_CLIPPING                    = 136,
D3DRS_LIGHTING                    = 137,
D3DRS_AMBIENT                     = 139,
D3DRS_FOGVERTEXMODE               = 140,
D3DRS_COLORVERTEX                 = 141,
D3DRS_LOCALVIEWER                 = 142,
D3DRS_NORMALIZENORMALS            = 143,
D3DRS_DIFFUSEMATERIALSOURCE       = 145,
D3DRS_SPECULARMATERIALSOURCE      = 146,
D3DRS_AMBIENTMATERIALSOURCE       = 147,
D3DRS_EMISSIVEMATERIALSOURCE      = 148,
D3DRS_VERTEXBLEND                 = 151,
D3DRS_CLIPPLANEENABLE             = 152,
D3DRS_POINTSIZE                   = 154,
D3DRS_POINTSIZE_MIN               = 155,
D3DRS_POINTSPRITEENABLE           = 156,
D3DRS_POINTSCALEENABLE            = 157,
D3DRS_POINTSCALE_A                = 158,
D3DRS_POINTSCALE_B                = 159,
D3DRS_POINTSCALE_C                = 160,
D3DRS_MULTISAMPLEANTIALIAS        = 161,
D3DRS_MULTISAMPLEMASK             = 162,
D3DRS_PATCHEDGESTYLE              = 163,
D3DRS_DEBUGMONITORTOKEN           = 165,
D3DRS_POINTSIZE_MAX               = 166,
D3DRS_INDEXEDVERTEXBLENDENABLE    = 167,
D3DRS_COLORWRITEENABLE            = 168,
D3DRS_TWEENFACTOR                 = 170,
D3DRS_BLENDOP                     = 171,
D3DRS_POSITIONDEGREE              = 172,
D3DRS_NORMALDEGREE                = 173,
D3DRS_SCISSORTESTENABLE           = 174,
D3DRS_SLOPESCALEDEPTHBIAS         = 175,
D3DRS_ANTIALIASEDLINEENABLE       = 176,
D3DRS_MINTESSELLATIONLEVEL        = 178,
D3DRS_MAXTESSELLATIONLEVEL        = 179,
D3DRS_ADAPTIVETESS_X              = 180,
D3DRS_ADAPTIVETESS_Y              = 181,
D3DRS_ADAPTIVETESS_Z              = 182,
D3DRS_ADAPTIVETESS_W              = 183,
D3DRS_ENABLEADAPTIVETESSELLATION  = 184,
D3DRS_TWOSIDEDSTENCILMODE         = 185,
D3DRS_CCW_STENCILFAIL             = 186,
D3DRS_CCW_STENCILZFAIL            = 187,
D3DRS_CCW_STENCILPASS             = 188,
D3DRS_CCW_STENCILFUNC             = 189,
D3DRS_COLORWRITEENABLE1           = 190,
D3DRS_COLORWRITEENABLE2           = 191,
D3DRS_COLORWRITEENABLE3           = 192,
D3DRS_BLENDFACTOR                 = 193,
D3DRS_SRGBWRITEENABLE             = 194,
D3DRS_DEPTHBIAS                   = 195,
D3DRS_WRAP8                       = 198,
D3DRS_WRAP9                       = 199,
D3DRS_WRAP10                      = 200,
D3DRS_WRAP11                      = 201,
D3DRS_WRAP12                      = 202,
D3DRS_WRAP13                      = 203,
D3DRS_WRAP14                      = 204,
D3DRS_WRAP15                      = 205,
D3DRS_SEPARATEALPHABLENDENABLE    = 206,
D3DRS_SRCBLENDALPHA               = 207,
D3DRS_DESTBLENDALPHA              = 208,
D3DRS_BLENDOPALPHA                = 209,
*/

/////////////////////////////////////////////////////////////
/// Flags de création de buffer
///
/// \param Flags : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
unsigned long DX9Enum::BufferFlags(unsigned long Flags)
{
    return (Flags & BUF_DYNAMIC ? D3DUSAGE_DYNAMIC : 0);
}


/////////////////////////////////////////////////////////////
/// Flags de verrouillage
///
/// \param Flags : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
unsigned long DX9Enum::LockFlags(unsigned long Flags)
{
    unsigned long LockFlags = 0;

    if (Flags & LOCK_READONLY)
        LockFlags = D3DLOCK_READONLY;

    if (Flags & LOCK_WRITEONLY)
    {
        LockFlags = D3DLOCK_DISCARD;
        //LockFlags = D3DLOCK_NOOVERWRITE;
    }

    return LockFlags;
}


/////////////////////////////////////////////////////////////
/// Type des matrices
///
/// \param Value : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
/*D3DTRANSFORMSTATETYPE DX9Enum::Get(MatrixType::TMatrixType Value)
{
    return MatrixType[Value];
}*/


/////////////////////////////////////////////////////////////
/// Type des prmitives
///
/// \param Value : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
D3DPRIMITIVETYPE DX9Enum::Get(PrimitiveType::TPrimitiveType Value)
{
    return PrimitiveType[Value];
}


/////////////////////////////////////////////////////////////
/// Formats de pixel
///
/// \param Value : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
D3DFORMAT DX9Enum::Get(PixelFormat::TPixelFormat Value)
{
    return PixelFormat[Value];
}


/////////////////////////////////////////////////////////////
/// Paramètres d'alpha-blending
///
/// \param Value : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
D3DBLEND DX9Enum::Get(Blend::TBlend Value)
{
    return Blend[Value];
}


/////////////////////////////////////////////////////////////
/// Opérations sur les unités de texture
///
/// \param Value : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
D3DTEXTUREOP DX9Enum::Get(TextureOperation::TTextureOp Value)
{
    return TextureOp[Value];
}


/////////////////////////////////////////////////////////////
/// Arguments des unités de texture
///
/// \param Value : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
unsigned long DX9Enum::Get(TTextureArg Value)
{
    return TextureArg[Value];
}

D3DSTENCILOP DX9Enum::Get(RenderParameter::TStencilOperation Value)
{
	return StencilOperation[Value];
}

D3DCMPFUNC DX9Enum::Get(TCompareFunction Value)
{
	return CompareFunction[Value];
}


/////////////////////////////////////////////////////////////
/// Paramètres de rendu
///
/// \param Value : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
D3DRENDERSTATETYPE DX9Enum::Get(RenderParameter::TRenderParameter Value)
{
    return RenderParameter[Value];
}

} // namespace CasaEngine
