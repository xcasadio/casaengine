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

#include "Base.h"
#include "GLEnum.h"


namespace CasaEngine
{

////////////////////////////////////////////////////////////
// Tables de correspondance
////////////////////////////////////////////////////////////
/*
GLenum GLEnum::MatrixType[] =
{
    GL_MODELVIEW,
    GL_PROJECTION,
    GL_TEXTURE,
    GL_TEXTURE,
    GL_TEXTURE,
    GL_TEXTURE
};
*/

/**
 * index from struct TPixelFormat, struct TPixelFmt {GLenum Format, Internal, Type;};
 */
GLEnum::TPixelFmt GLEnum::PixelFormat[] =
{
#if CA_PLATFORM_ANDROID

	{GL_LUMINANCE,       GL_LUMINANCE,                     GL_UNSIGNED_BYTE},
	{GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA,			   GL_UNSIGNED_BYTE},

	{GL_RGBA,        GL_RGB5_A1,                       GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT},
	{GL_RGBA,        GL_RGBA4,                         GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT},

	{GL_RGB,         GL_RGB,                          GL_UNSIGNED_BYTE},
	{GL_RGBA,	     GL_RGBA,                         GL_UNSIGNED_BYTE},

	{GL_RGB,         GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG,                         GL_UNSIGNED_BYTE},
	{GL_RGB,		 GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG,                         GL_UNSIGNED_BYTE},
	{GL_RGBA,        GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG,                        GL_UNSIGNED_BYTE},
	{GL_RGBA,        GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG,                        GL_UNSIGNED_BYTE},

	{GL_RGB,         GL_COMPRESSED_RGB_S3TC_DXT1_EXT,  0},
	{GL_RGBA,        GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 0},
	{0,        0, 0},
	{0,        0, 0}

#else

    {GL_LUMINANCE,       GL_LUMINANCE8,                    GL_UNSIGNED_BYTE},
    {GL_LUMINANCE_ALPHA, GL_LUMINANCE8_ALPHA8,             GL_UNSIGNED_BYTE},

    {GL_BGRA_EXT,        GL_RGB5_A1,                       GL_UNSIGNED_SHORT_1_5_5_5_REV},
    {GL_BGRA_EXT,        GL_RGBA4,                         GL_UNSIGNED_SHORT_4_4_4_4_REV},

    {GL_BGR,             GL_RGB8,                          GL_UNSIGNED_BYTE},
    {GL_BGRA_EXT,        GL_RGBA8,                         GL_UNSIGNED_BYTE},

	{0,        0,                        0},
	{0,		   0,                        0},
	{0,        0,                        0},
	{0,        0,                        0},

	{GL_BGR,             GL_COMPRESSED_RGB_S3TC_DXT1_EXT,  0},
    {GL_BGRA,            GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 0},
    {GL_BGRA,            GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, 0},
    {GL_BGRA,            GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 0}

#endif
};
GLenum GLEnum::Blend[] =
{
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_SRC_COLOR,
    GL_ONE_MINUS_SRC_COLOR,
    GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR,
    GL_ONE,
    GL_ZERO
};

#if CA_PLATFORM_DESKTOP

GLenum GLEnum::TextureOp[] =
{
	GL_REPLACE,
	GL_ADD,
	GL_MODULATE,
	GL_REPLACE,
	GL_ADD,
	GL_MODULATE
};

GLenum GLEnum::TextureArg[] =
{
    GL_PRIMARY_COLOR_EXT,
    GL_TEXTURE,
    GL_PREVIOUS_EXT,
    GL_CONSTANT_EXT
};

GLenum GLEnum::FillMode[] =
{
	0, // not used
	GL_POINT,
	GL_LINE,
	GL_FILL
};

#endif // CA_PLATFORM_DESKTOP

GLenum GLEnum::CompareFunction[] =
{
	GL_ALWAYS,
	GL_NEVER,
	GL_LESS,
	GL_LEQUAL,
	GL_EQUAL,
	GL_GEQUAL,
	GL_GREATER,
	GL_NOTEQUAL	
};

GLenum GLEnum::StencilOperation[] =
{
	GL_KEEP,
	GL_ZERO,
	GL_REPLACE,
	GL_INCR,
	GL_DECR,
	0, // GL_INCRSAT,
	0, // GL_DECRSAT,
	GL_INVERT
};
GLenum GLEnum::RenderParameter[] =
{
	GL_DEPTH_TEST,
    0, // ZWrite
    GL_BLEND,
	GL_CULL_FACE,
	0, // FillMode, not used
	GL_SCISSOR_TEST,
	GL_STENCIL_TEST,
	GL_STENCIL_FAIL,
	GL_STENCIL_PASS_DEPTH_FAIL,
	GL_STENCIL_PASS_DEPTH_PASS,	 
	GL_STENCIL_FUNC,
	GL_STENCIL_REF,
	GL_STENCIL_VALUE_MASK,
	GL_STENCIL_WRITEMASK,
	//GL_STENCIL_CLEAR_VALUE
};

/////////////////////////////////////////////////////////////
/// Flags de création de buffer
///
/// \param Flags : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
unsigned long GLEnum::BufferFlags(unsigned long Flags)
{
    // TODO : trouver pourquoi GL_STATIC_DRAW_ARB est plus performant que DYNAMIC ou STREAM pour les buffers dynamiques
    //        (taille du buffer ?)

	// 3 types DRAW, READ, COPY

#if CA_PLATFORM_ANDROID

	// GL_STREAM_DRAW ?
	return (Flags & BUF_DYNAMIC ? GL_DYNAMIC_DRAW : 
		Flags & BUF_STREAM ? GL_STREAM_DRAW : GL_STATIC_DRAW);

#else

	return (Flags & BUF_DYNAMIC ? GL_DYNAMIC_DRAW_ARB : 
		Flags & BUF_STREAM ? GL_STREAM_DRAW_ARB : GL_STATIC_DRAW_ARB);

#endif // CA_PLATFORM_ANDROID
}


/////////////////////////////////////////////////////////////
/// Flags de verrouillage
///
/// \param Flags : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
unsigned long GLEnum::LockFlags(unsigned long Flags)
{
	unsigned long LockFlags = 0;

#if CA_PLATFORM_ANDROID

	// TODO 
	// #define GL_BUFFER_MAPPED_OES                                    0x88BC
	// #define GL_BUFFER_MAP_POINTER_OES                               0x88BD

	if (Flags & LOCK_READONLY)  LockFlags = GL_BUFFER_ACCESS_OES;
	else if (Flags & LOCK_WRITEONLY) LockFlags = GL_WRITE_ONLY_OES;
	else LockFlags = GL_BUFFER_ACCESS_OES;

#else

	if (Flags & LOCK_READONLY)  LockFlags = GL_READ_ONLY_ARB;
	else if (Flags & LOCK_WRITEONLY) LockFlags = GL_WRITE_ONLY_ARB;
	else LockFlags = GL_READ_WRITE_ARB;

#endif // CA_PLATFORM_ANDROID
	
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
/*GLenum GLEnum::Get(MatrixType::TMatrixType Value)
{
    return MatrixType[Value];
}*/


/////////////////////////////////////////////////////////////
/// Formats de pixel
///
/// \param Value : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
GLEnum::TPixelFmt GLEnum::Get(PixelFormat::TPixelFormat Value)
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
GLenum GLEnum::Get(Blend::TBlend Value)
{
    return Blend[Value];
}

#if CA_PLATFORM_DESKTOP

/////////////////////////////////////////////////////////////
/// Opérations sur les unités de texture
///
/// \param Value : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
GLenum GLEnum::Get(TextureOperation::TTextureOp Value)
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
GLenum GLEnum::Get(TTextureArg Value)
{
    return TextureArg[Value];
}

/////////////////////////////////////////////////////////////
/// Paramètres de rendu
///
/// \param Value : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
GLenum GLEnum::Get(RenderParameter::TFillMode Value)
{
	return FillMode[Value];
}

#endif // CA_PLATFORM_DESKTOP


/**
 * 
 */
GLenum GLEnum::Get(TCompareFunction Value)
{
	return CompareFunction[Value];
}

/**
 * 
 */
GLenum GLEnum::Get(RenderParameter::TStencilOperation Value)
{
	return StencilOperation[Value];
}

/////////////////////////////////////////////////////////////
/// Paramètres de rendu
///
/// \param Value : Valeur à convertir
///
/// \return Valeur convertie
///
////////////////////////////////////////////////////////////
GLenum GLEnum::Get(RenderParameter::TRenderParameter Value)
{
    return RenderParameter[Value];
}

} // namespace CasaEngine
