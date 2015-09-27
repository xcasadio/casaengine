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

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else

#include "Win32/Win32Macro.h"
#include "SFML/System/NonCopyable.hpp"

#include <GL/glew.h>
#include <gl/gl.h>
#include "Extensions/glext.h"

#include <gl/glu.h>

#endif // #if CA_PLATFORM_ANDROID

#include "GLBuffer.h"
#include "GLDeclaration.h"
#include "GLEffect.h"
#include "GLEnum.h"
#include "GLMacro.h"
#include "GLRenderTargetTexture.h"
#include "GLRenderer.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "Graphics/Color.h"
#include "Graphics/PixelUtils.h"
#include "Graphics/Vertices/DeclarationElement.h"
#include "Graphics/Viewport.h"
#include "Maths/Matrix4.h"
#include "Util.h"
#include "Macro.h"
#include "Log/LogManager.h"



namespace CasaEngine
{

SINGLETON_IMPL(GLRenderer)

////////////////////////////////////////////////////////////
// Macro de calcul d'offset pour les buffers
////////////////////////////////////////////////////////////
#define BUFFER_OFFSET(n) ((char*)nullptr + (n))

////////////////////////////////////////////////////////////
// Fonction et macro facilitant le chargement des extensions
////////////////////////////////////////////////////////////
template <class T> inline void LoadExtension(T& Proc, const char* Name)
{

#if CA_PLATFORM_ANDROID

	Proc = reinterpret_cast<T>(eglGetProcAddress(Name));

#else

	Proc = reinterpret_cast<T>(wglGetProcAddress(Name));

#endif
	
}

#define LOAD_EXTENSION(Ext) LoadExtension(Ext, #Ext)


#if CA_PLATFORM_WINDOWS

////////////////////////////////////////////////////////////
// Données statiques
////////////////////////////////////////////////////////////
PFNGLBINDBUFFERARBPROC               GLRenderer::glBindBufferARB;
PFNGLDELETEBUFFERSARBPROC            GLRenderer::glDeleteBuffersARB;
PFNGLGENBUFFERSARBPROC               GLRenderer::glGenBuffersARB;
PFNGLBUFFERDATAARBPROC               GLRenderer::glBufferDataARB;
PFNGLBUFFERSUBDATAARBPROC            GLRenderer::glBufferSubDataARB;
PFNGLGETBUFFERSUBDATAARBPROC         GLRenderer::glGetBufferSubDataARB;
PFNGLMAPBUFFERARBPROC                GLRenderer::glMapBufferARB;
PFNGLUNMAPBUFFERARBPROC              GLRenderer::glUnmapBufferARB;
PFNGLACTIVETEXTUREARBPROC            GLRenderer::glActiveTextureARB;
PFNGLCLIENTACTIVETEXTUREARBPROC      GLRenderer::glClientActiveTextureARB;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC     GLRenderer::glCompressedTexImage2DARB;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC  GLRenderer::glCompressedTexSubImage2DARB;
PFNGLGENPROGRAMSARBPROC              GLRenderer::glGenProgramsARB;
PFNGLBINDPROGRAMARBPROC              GLRenderer::glBindProgramARB;
PFNGLPROGRAMSTRINGARBPROC            GLRenderer::glProgramStringARB;
PFNGLDELETEPROGRAMSARBPROC           GLRenderer::glDeleteProgramsARB;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC GLRenderer::glProgramLocalParameter4fvARB;
PFNGLCREATEPROGRAMOBJECTARBPROC      GLRenderer::glCreateProgramObjectARB;
PFNGLCREATESHADEROBJECTARBPROC       GLRenderer::glCreateShaderObjectARB;
PFNGLSHADERSOURCEARBPROC             GLRenderer::glShaderSourceARB;
PFNGLCOMPILESHADERARBPROC            GLRenderer::glCompileShaderARB;
PFNGLATTACHOBJECTARBPROC             GLRenderer::glAttachObjectARB;
PFNGLLINKPROGRAMARBPROC              GLRenderer::glLinkProgramARB;
PFNGLGETOBJECTPARAMETERIVARBPROC     GLRenderer::glGetObjectParameterivARB;
PFNGLGETACTIVEUNIFORMARBPROC         GLRenderer::glGetActiveUniformARB;
PFNGLGETUNIFORMLOCATIONARBPROC       GLRenderer::glGetUniformLocationARB;
PFNGLUSEPROGRAMOBJECTARBPROC         GLRenderer::glUseProgramObjectARB;
PFNGLUNIFORM4FARBPROC                GLRenderer::glUniform4fARB;
PFNGLDELETEOBJECTARBPROC             GLRenderer::glDeleteObjectARB;
PFNGLCOMBINERSTAGEPARAMETERFVNVPROC  GLRenderer::glCombinerStageParameterfvNV;

#else

PFNGLMAPBUFFEROESPROC				GLRenderer::glMapBufferOES;
PFNGLUNMAPBUFFEROESPROC				GLRenderer::glUnmapBufferOES;

#endif // #if CA_PLATFORM_WINDOWS

/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
////////////////////////////////////////////////////////////
GLRenderer::GLRenderer() :
	m_CurrentDeclaration(nullptr),
		m_pWindow(nullptr),
	m_IndexStride       (0),
	m_Extensions        ("")
{

}


/////////////////////////////////////////////////////////////
/// Destructeur
///
////////////////////////////////////////////////////////////
GLRenderer::~GLRenderer()
{
}


////////////////////////////////////////////////////////////
// Renvoie une description du renderer courant
///
/// \return Chaîne de caractère décrivant le renderer et sa version
///
////////////////////////////////////////////////////////////
std::string GLRenderer::GetRendererDesc() const
{
    return std::string("OpenGL ") +
		+ reinterpret_cast<const char*>(glGetString(GL_VERSION))
		+ " (" +
		+ reinterpret_cast<const char*>(glGetString(GL_VENDOR))
		+ ", " +
		+ reinterpret_cast<const char*>(glGetString(GL_RENDERER))
		+ ")";
}

/////////////////////////////////////////////////////////////
/// Initialise l'API
///
/// \param Hwnd : Handle du contrôle de rendu
///
////////////////////////////////////////////////////////////

#if CA_PLATFORM_DESKTOP

void GLRenderer::Setup(sf::Window *m_pWindow_)
{
	m_pWindow = m_pWindow_;

    // Récupération du Hwnd et du HDC de la fenêtre de rendu
    //m_Hwnd   = reinterpret_cast<HWND>(windowHandle_);
    //m_Handle = GetDC(m_Hwnd); //GetWindowDC(m_Hwnd);

    // Choix du meilleur format de pixel
    //if (!SetPixelFormat(m_Handle, ChoosePixelFormat(m_Handle, &PixelDescriptor), &PixelDescriptor))
    //    throw GLException("SetPixelFormat", "Initialize");

    // Création du contexte de rendu
    //m_Context = wglCreateContext(m_Handle);
    //if (!wglMakeCurrent(m_Handle, m_Context))
    //    throw GLException("wglMakeCurrent", "Initialize");

    // Récupération des extensions supportées
    m_Extensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));

    // Chargement des extensions
    LoadExtensions();

	//init GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		CA_ERROR("GLEW fatal error : %s", glewGetErrorString(err));
		exit(1); // or handle the error in a nicer way
	}

	//if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
	//	exit(1); // or handle the error in a nicer way

    // States par défaut
    GLCheck(glClearDepth(1.0f));
    GLCheck(glClearStencil(0x00));
    GLCheck(glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST));
    //GLCheck(glShadeModel(GL_SMOOTH));
    GLCheck(glEnable(GL_DEPTH_TEST));
}

#else

void GLRenderer::Setup()
{

	// Récupération des extensions supportées
	m_Extensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));

	// Chargement des extensions
	LoadExtensions();

	// States par défaut
	/*float color[4];
	CColor::CornflowerBlue.ToFloat(color);
	GLCheck(glClearColor(color[0], color[1], color[2], color[3]));*/
	//GLCheck(glClearDepth(1.0f));
	GLCheck(glClearStencil(0x00));
	//GLCheck(glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST));
	//GLCheck(glShadeModel(GL_SMOOTH));
	GLCheck(glEnable(GL_DEPTH_TEST));

}

#endif // #if CA_PLATFORM_DESKTOP


////////////////////////////////////////////////////////////
/// Vérifie les fonctionnalités supportées et met à jour
/// la table des fonctionnalités
///
////////////////////////////////////////////////////////////
void GLRenderer::CheckCaps()
{
    m_Capabilities[Capability::HardwareMipmapping] = CheckExtension("GL_SGIS_generate_mipmap");
    m_Capabilities[Capability::DXTCompression] = CheckExtension("GL_ARB_texture_compression") &&
                                          CheckExtension("GL_EXT_texture_compression_s3tc");
    m_Capabilities[Capability::TextureNonPowerOf2] = CheckExtension("GL_ARB_texture_non_power_of_two");
	m_Capabilities[Capability::ScissorTest] = true;

	GLCheck(glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_MaxTextureSize.x));
	m_MaxTextureSize.y = m_MaxTextureSize.x;
}


/////////////////////////////////////////////////////////////
/// Vérifie le support d'une extension
///
/// \param Extension : Extension à vérifier
///
////////////////////////////////////////////////////////////
bool GLRenderer::CheckExtension(const std::string& Extension) const
{
    return m_Extensions.find(Extension) != std::string::npos;
}



/////////////////////////////////////////////////////////////
/// Charge les extensions OpenGL
///
////////////////////////////////////////////////////////////
void GLRenderer::LoadExtensions()
{

#if CA_PLATFORM_DESKTOP

    LOAD_EXTENSION(glBindBufferARB);
    LOAD_EXTENSION(glDeleteBuffersARB);
    LOAD_EXTENSION(glGenBuffersARB);
    LOAD_EXTENSION(glBufferDataARB);
    LOAD_EXTENSION(glBufferSubDataARB);
    LOAD_EXTENSION(glGetBufferSubDataARB);
    LOAD_EXTENSION(glMapBufferARB);
    LOAD_EXTENSION(glUnmapBufferARB);
    LOAD_EXTENSION(glActiveTextureARB);
    LOAD_EXTENSION(glClientActiveTextureARB);
    LOAD_EXTENSION(glCompressedTexImage2DARB);
    LOAD_EXTENSION(glCompressedTexSubImage2DARB);
    LOAD_EXTENSION(glGenProgramsARB);
    LOAD_EXTENSION(glBindProgramARB);
    LOAD_EXTENSION(glProgramStringARB);
    LOAD_EXTENSION(glDeleteProgramsARB);
    LOAD_EXTENSION(glProgramLocalParameter4fvARB);
    LOAD_EXTENSION(glCreateProgramObjectARB);
    LOAD_EXTENSION(glCreateShaderObjectARB);
    LOAD_EXTENSION(glShaderSourceARB);
    LOAD_EXTENSION(glCompileShaderARB);
    LOAD_EXTENSION(glAttachObjectARB);
    LOAD_EXTENSION(glLinkProgramARB);
    LOAD_EXTENSION(glGetObjectParameterivARB);
    LOAD_EXTENSION(glGetActiveUniformARB);
    LOAD_EXTENSION(glGetUniformLocationARB);
    LOAD_EXTENSION(glUseProgramObjectARB);
    LOAD_EXTENSION(glUniform4fARB);
    LOAD_EXTENSION(glDeleteObjectARB);
    LOAD_EXTENSION(glCombinerStageParameterfvNV);

#else

	LOAD_EXTENSION(glMapBufferOES);
	LOAD_EXTENSION(glUnmapBufferOES);

#endif // #if CA_PLATFORM_DESKTOP

}

/**
 * 
 */
const char * GLRenderer::GetShaderFileExtension() const
{
	return ".vert";
}

/////////////////////////////////////////////////////////////
/// Démarre le rendu de la scène
///
////////////////////////////////////////////////////////////
void GLRenderer::BeginScene()
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


/////////////////////////////////////////////////////////////
/// Termine le rendu de la scène
///
////////////////////////////////////////////////////////////
void GLRenderer::EndScene()
{
#if CA_PLATFORM_DESKTOP

    //Win32Check(SwapBuffers(m_Handle)); 
	m_pWindow->display();

#endif // #if CA_PLATFORM_DESKTOP
}

/**
 * 
 */
void GLRenderer::Clear(unsigned int flags)
{
	unsigned int f = 0;

	if ((flags & RenderParameter::Color) == RenderParameter::Color)
	{
		f |= GL_COLOR_BUFFER_BIT;
	}

	if ((flags & RenderParameter::ZBuffer) == RenderParameter::ZBuffer)
	{
		f |= GL_DEPTH_BUFFER_BIT;
	}

	if ((flags & RenderParameter::Stencil) == RenderParameter::Stencil)
	{
		f |= GL_STENCIL_BUFFER_BIT;
	}

	glClear(f);
}


/**
 * Create a vertex Buffer
 * 
 * \param Size :   Nombre d'éléments
 * \param Stride : Taille d'un élément
 * \param Flags :  Options de création
 * 
 * \return Pointeur sur le nouveau buffer
 * 
 */
IBufferBase* GLRenderer::CreateVB(unsigned long Size, unsigned long Stride, unsigned long Flags) const
{
	unsigned int VertexBuffer = 0;

#if CA_PLATFORM_MOBILE

	GLCheck(glGenBuffers(1, &VertexBuffer));

	GLCheck(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer));
	GLCheck(glBufferData(GL_ARRAY_BUFFER, Size * Stride, nullptr, GLEnum::BufferFlags(Flags)));

#else

	GLCheck(glGenBuffersARB(1, &VertexBuffer));

	GLCheck(glBindBufferARB(GL_ARRAY_BUFFER_ARB, VertexBuffer));
	GLCheck(glBufferDataARB(GL_ARRAY_BUFFER_ARB, Size * Stride, nullptr, GLEnum::BufferFlags(Flags)));

#endif // #if CA_PLATFORM_MOBILE

    return NEW_AO GLVertexBuffer(Size, VertexBuffer);
}

/**
 * Create a index Buffer
 * 
 * \param Size :   Nombre d'éléments
 * \param Stride : Taille d'un élément
 * \param Flags :  Options de création
 * 
 * \return Pointeur sur le nouveau buffer
 * 
 */
IBufferBase* GLRenderer::CreateIB(unsigned long Size, unsigned long Stride, unsigned long Flags) const
{
	unsigned int IndexBuffer = 0;

#if CA_PLATFORM_MOBILE

	GLCheck(glGenBuffers(1, &IndexBuffer));

	GLCheck(glBindBuffer(GL_ARRAY_BUFFER, IndexBuffer));
	GLCheck(glBufferData(GL_ARRAY_BUFFER, Size * Stride, nullptr, GLEnum::BufferFlags(Flags)));

#else

	GLCheck(glGenBuffersARB(1, &IndexBuffer));

	GLCheck(glBindBufferARB(GL_ARRAY_BUFFER_ARB, IndexBuffer));
	GLCheck(glBufferDataARB(GL_ARRAY_BUFFER_ARB, Size * Stride, nullptr, GLEnum::BufferFlags(Flags)));

#endif // #if CA_PLATFORM_MOBILE

    return NEW_AO GLIndexBuffer(Size, IndexBuffer);
}



/////////////////////////////////////////////////////////////
/// Crée une déclaration de vertex
///
/// \param Elements : Description de la déclaration
/// \param Count :    Nombre d'éléments dans le tableau
///
/// \return Pointeur sur la déclaration créée
///
////////////////////////////////////////////////////////////
IDeclaration* GLRenderer::CreateDeclaration(const DeclarationElement::TDeclarationElement* Elements, std::size_t Count) const
{
    GLDeclaration* Declaration = NEW_AO GLDeclaration;

    std::vector<int> Offset(1, 0);

    for (const DeclarationElement::TDeclarationElement* Elt = Elements; Elt < Elements + Count; ++Elt)
    {
        // Construction de l'élément GL correspondant
        GLDeclaration::TElement CurrentElement;
        CurrentElement.Usage  = Elt->Usage;
        CurrentElement.Type   = Elt->DataType;

		while (Offset.size() <= Elt->Stream)
		{
			Offset.push_back(0);
		}

        CurrentElement.Offset = Offset[Elt->Stream];

        // Ajout de l'élément courant
        Declaration->AddElement(Elt->Stream, CurrentElement);

        // Incrémentation de l'offset
        static const unsigned int Size[] = {
			sizeof(float), 
			2 * sizeof(float), 
			3 * sizeof(float), 
			4 * sizeof(float), 
			sizeof(unsigned char)};
        Offset[Elt->Stream] += Size[Elt->DataType];
		/*
		Float1, ///< 1 flottant
		Float2, ///< 2 floattants
		Float3, ///< 3 floattants
		Float4, ///< 4 floattants
		Color   ///< Couleur (entier long non signé)
		*/
    }

    return Declaration;
}


/////////////////////////////////////////////////////////////
/// Change le vertex buffer courant
///
/// \param Stream :    Numéro du stream
/// \param Buffer :    Pointeur sur le buffer
/// \param Stride :    Taille des vertices
/// \param MinVertex : Indice de vertex minimum
/// \param MaxVertex : Indice de vertex maximum
///
////////////////////////////////////////////////////////////
void GLRenderer::SetVB(unsigned int Stream, const IBufferBase* Buffer, unsigned long Stride, unsigned long MinVertex, unsigned long /*MaxVertex*/)
{
	CA_ASSERT(m_CurrentDeclaration != nullptr, "Set a Declaration before call GLRenderer::SetVB()");

    const GLVertexBuffer* VertexBuffer = static_cast<const GLVertexBuffer*>(Buffer);

#if CA_PLATFORM_MOBILE

    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer->GetBuffer()));
	static const unsigned int Size[] = {1, 2, 3, 4, 4};

#else

	GLCheck(glBindBufferARB(GL_ARRAY_BUFFER_ARB, VertexBuffer->GetBuffer()));
	static const unsigned int Size[] = {1, 2, 3, 4, GL_BGRA};

#endif // CA_PLATFORM_MOBILE
	    
    static const unsigned int Type[] = {GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE};

	int index = 0;
    const GLDeclaration::TElementArray& StreamDesc = m_CurrentDeclaration->GetStreamElements(Stream);
    for (GLDeclaration::TElementArray::const_iterator i = StreamDesc.begin(); i != StreamDesc.end(); ++i)
    {
		GLCheck(glEnableVertexAttribArray(index));
		//GLCheck(glVertexAttribDivisor(index, 0));
		GLboolean normalized = GL_FALSE;

		if (i->Usage == DeclarationElement::Diffuse)
		{
			normalized = GL_TRUE;
		}

		GLCheck(glVertexAttribPointer(
			index, Size[i->Type], Type[i->Type], normalized, Stride, BUFFER_OFFSET(i->Offset + MinVertex * Stride)));

		index++;
    }
}


/////////////////////////////////////////////////////////////
/// Change le index buffer courant
///
/// \param Buffer : Pointeur sur le buffer
/// \param Stride : Taille des indices
///
////////////////////////////////////////////////////////////
void GLRenderer::SetIB(const IBufferBase* Buffer, unsigned long Stride)
{
    const GLIndexBuffer* IndexBuffer = static_cast<const GLIndexBuffer*>(Buffer);

#if CA_PLATFORM_MOBILE

	GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->GetBuffer()));

#else

	GLCheck(glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IndexBuffer->GetBuffer()));

#endif // CA_PLATFORM_MOBILE
    
    m_IndexStride = Stride;
}


/////////////////////////////////////////////////////////////
/// Change la déclaration de vertex courante
///
/// \param Declaration : Nouvelle déclaration
///
////////////////////////////////////////////////////////////
void GLRenderer::SetDeclaration(const IDeclaration* Declaration)
{
    for (int i = 0; i < 4; ++i)
    {
		GLCheck(glDisableVertexAttribArray(i));

#if CA_PLATFORM_MOBILE

		GLCheck(glActiveTexture(GL_TEXTURE0 + i));

#else

		GLCheck(glActiveTextureARB(GL_TEXTURE0_ARB + i));

#endif // CA_PLATFORM_MOBILE
        
        //glDisable(GL_TEXTURE_2D);
    }

    m_CurrentDeclaration = static_cast<const GLDeclaration*>(Declaration);
}


/////////////////////////////////////////////////////////////
/// Affiche des primitives
///
/// \param Type :        Type de primitives
/// \param FirstVertex : Position du premier vertex
/// \param Count :       Nombre de triangles
///
////////////////////////////////////////////////////////////
void GLRenderer::DrawPrimitives(PrimitiveType::TPrimitiveType Type, unsigned long FirstVertex, unsigned long Count) const
{
    // Affichage des primitives
    switch (Type)
    {
	case PrimitiveType::TriangleList :  GLCheck(glDrawArrays(GL_TRIANGLES,      FirstVertex, Count * 3)); break;
	case PrimitiveType::TriangleStrip : GLCheck(glDrawArrays(GL_TRIANGLE_STRIP, FirstVertex, Count + 2)); break;
	case PrimitiveType::TriangleFan :   GLCheck(glDrawArrays(GL_TRIANGLE_FAN,   FirstVertex, Count + 1)); break;
	case PrimitiveType::LineList :      GLCheck(glDrawArrays(GL_LINES,          FirstVertex, Count * 2)); break; 
	case PrimitiveType::LineStrip :     GLCheck(glDrawArrays(GL_LINE_STRIP,     FirstVertex, Count + 1)); break;
    case PrimitiveType::PointList :     GLCheck(glDrawArrays(GL_POINTS,         FirstVertex, Count    )); break;
    }
}


/////////////////////////////////////////////////////////////
/// Affiche des primitives indicées
///
/// \param Type :       Type de primitives
/// \param FirstIndex : Position du premier indice
/// \param Count :      Nombre de triangles
///
////////////////////////////////////////////////////////////
void GLRenderer::DrawIndexedPrimitives(PrimitiveType::TPrimitiveType Type, unsigned long FirstIndex, unsigned long Count) const
{
    // Quelques calculs
    unsigned long IndicesType = (m_IndexStride == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT);
    const void*   Offset      = BUFFER_OFFSET(FirstIndex * m_IndexStride);

    // Affichage des primitives
    switch (Type)
    {
        case PrimitiveType::TriangleList :  GLCheck(glDrawElements(GL_TRIANGLES,      Count * 3, IndicesType, Offset)); break;
        case PrimitiveType::TriangleStrip : GLCheck(glDrawElements(GL_TRIANGLE_STRIP, Count + 2, IndicesType, Offset)); break;
        case PrimitiveType::TriangleFan :   GLCheck(glDrawElements(GL_TRIANGLE_FAN,   Count + 1, IndicesType, Offset)); break;
        case PrimitiveType::LineList :      GLCheck(glDrawElements(GL_LINES,          Count * 2, IndicesType, Offset)); break; 
        case PrimitiveType::LineStrip :     GLCheck(glDrawElements(GL_LINE_STRIP,     Count + 1, IndicesType, Offset)); break;
        case PrimitiveType::PointList :     GLCheck(glDrawElements(GL_POINTS,         Count,     IndicesType, Offset)); break;
    }
}

#if CA_PLATFORM_DESKTOP

//IRenderer::Get().DrawIndexedPrimitivesInstanced(PrimitiveType::TriangleList, 0, 4, m_NbElt);
/////////////////////////////////////////////////////////////
/// Affiche des primitives
///
/// \param Type :        Type de primitives
/// \param FirstVertex : Position du premier vertex
/// \param Count :       Nombre de triangles
///
////////////////////////////////////////////////////////////
void GLRenderer::DrawPrimitivesInstanced(PrimitiveType::TPrimitiveType Type, unsigned long FirstVertex, unsigned long Count, unsigned long nbElt_) const
{
	// Affichage des primitives
	switch (Type)
	{
	case PrimitiveType::TriangleList :  GLCheck(glDrawArraysInstanced(GL_TRIANGLES,      FirstVertex, Count * 3, nbElt_)); break;
	case PrimitiveType::TriangleStrip : GLCheck(glDrawArraysInstanced(GL_TRIANGLE_STRIP, FirstVertex, Count + 2, nbElt_)); break;
	case PrimitiveType::TriangleFan :   GLCheck(glDrawArraysInstanced(GL_TRIANGLE_FAN,   FirstVertex, Count + 1, nbElt_)); break;
	case PrimitiveType::LineList :      GLCheck(glDrawArraysInstanced(GL_LINES,          FirstVertex, Count * 2, nbElt_)); break; 
	case PrimitiveType::LineStrip :     GLCheck(glDrawArraysInstanced(GL_LINE_STRIP,     FirstVertex, Count + 1, nbElt_)); break;
	case PrimitiveType::PointList :     GLCheck(glDrawArraysInstanced(GL_POINTS,         FirstVertex, Count	   , nbElt_)); break;
	}
}


/////////////////////////////////////////////////////////////
/// Affiche des primitives indicées
///
/// \param Type :       Type de primitives
/// \param FirstIndex : Position du premier indice
/// \param Count :      Nombre de triangles
///
////////////////////////////////////////////////////////////
void GLRenderer::DrawIndexedPrimitivesInstanced(PrimitiveType::TPrimitiveType Type, unsigned long FirstIndex, unsigned long Count, unsigned long nbElt_) const
{
	// Quelques calculs
	unsigned long IndicesType = (m_IndexStride == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT);
	const void*   Offset      = BUFFER_OFFSET(FirstIndex * m_IndexStride);

	// Affichage des primitives
	switch (Type)
	{
	case PrimitiveType::TriangleList :  GLCheck(glDrawElementsInstanced(GL_TRIANGLES,      Count * 3, IndicesType, Offset, nbElt_)); break;
	case PrimitiveType::TriangleStrip : GLCheck(glDrawElementsInstanced(GL_TRIANGLE_STRIP, Count + 2, IndicesType, Offset, nbElt_)); break;
	case PrimitiveType::TriangleFan :   GLCheck(glDrawElementsInstanced(GL_TRIANGLE_FAN,   Count + 1, IndicesType, Offset, nbElt_)); break;
	case PrimitiveType::LineList :      GLCheck(glDrawElementsInstanced(GL_LINES,          Count * 2, IndicesType, Offset, nbElt_)); break; 
	case PrimitiveType::LineStrip :     GLCheck(glDrawElementsInstanced(GL_LINE_STRIP,     Count + 1, IndicesType, Offset, nbElt_)); break;
	case PrimitiveType::PointList :     GLCheck(glDrawElementsInstanced(GL_POINTS,         Count,     IndicesType, Offset, nbElt_)); break;
	}
}

#endif // CA_PLATFORM_DESKTOP

////////////////////////////////////////////////////////////////
/// Empile la matrice courante
///
/// \param Type : Type de la matrice
///
////////////////////////////////////////////////////////////
/*void GLRenderer::PushMatrix(MatrixType::TMatrixType Type)
{
    if (Type >= MatrixType::Texture0)
        GLCheck(glActiveTextureARB(GL_TEXTURE0_ARB + Type - MatrixType::Texture0));

    GLCheck(glMatrixMode(GLEnum::Get(Type)));
    GLCheck(glPushMatrix());
}*/


/////////////////////////////////////////////////////////////
/// Dépile la matrice en haut de la pile
///
/// \param Type : Type de la matrice
///
////////////////////////////////////////////////////////////
/*void GLRenderer::PopMatrix(MatrixType::TMatrixType Type)
{
    if (Type >= MatrixType::Texture0)
        GLCheck(glActiveTextureARB(GL_TEXTURE0_ARB + Type - MatrixType::Texture0));

    GLCheck(glMatrixMode(GLEnum::Get(Type)));
    GLCheck(glPopMatrix());
}*/


/////////////////////////////////////////////////////////////
/// Charge une matrice
///
/// \param Type :   Type de la matrice
/// \param Matrix : Nouvelle matrice
///
////////////////////////////////////////////////////////////
/*void GLRenderer::LoadMatrix(MatrixType::TMatrixType Type, const Matrix4& Matrix)
{
    if (Type >= MatrixType::Texture0)
        GLCheck(glActiveTextureARB(GL_TEXTURE0_ARB + Type - MatrixType::Texture0));

    GLCheck(glMatrixMode(GLEnum::Get(Type)));
    GLCheck(glLoadMatrixf(Matrix));
}*/


/////////////////////////////////////////////////////////////
/// Charge une matrice en la multipliant avec la précédente
///
/// \param Type :   Type de la matrice
/// \param Matrix : Nouvelle matrice
///
////////////////////////////////////////////////////////////
/*void GLRenderer::LoadMatrixMult(MatrixType::TMatrixType Type, const Matrix4& Matrix)
{
    if (Type >= MatrixType::Texture0)
        GLCheck(glActiveTextureARB(GL_TEXTURE0_ARB + Type - MatrixType::Texture0));

    GLCheck(glMatrixMode(GLEnum::Get(Type)));
    GLCheck(glMultMatrixf(Matrix));
}*/


/////////////////////////////////////////////////////////////
/// Récupère la matrice courante
///
/// \param  Type :   Type de la matrice
/// \param Matrix : Matrice de destination
///
////////////////////////////////////////////////////////////
/*void GLRenderer::GetMatrix(MatrixType::TMatrixType Type, Matrix4& Matrix) const
{
    if (Type >= MatrixType::Texture0)
        GLCheck(glActiveTextureARB(GL_TEXTURE0_ARB + Type - MatrixType::Texture0));

    GLCheck(glGetFloatv(GLEnum::Get(Type), Matrix));
}*/


/////////////////////////////////////////////////////////////
/// Convertit une couleur dans le format pris en charge par l'API
///
/// \param Color : Couleur à convertir
///
/// \return Couleur convertie sous forme d'unsigned long
///
////////////////////////////////////////////////////////////
unsigned long GLRenderer::ConvertColor(const CColor& Color) const
{

#if CA_PLATFORM_MOBILE

	//return Color.ToRGBA();
	return Color.ToBGRA();

#else

	return Color.ToARGB();

#endif // CA_PLATFORM_MOBILE

}


/////////////////////////////////////////////////////////////
/// Change une texture
///
/// \param Unit :    Unité de texture
/// \param Texture : Nouvelle texture
///
////////////////////////////////////////////////////////////
void GLRenderer::SetTexture(unsigned int Unit, const ITextureBase* Texture) const
{

#if CA_PLATFORM_MOBILE

	CA_ASSERT(Unit < 8, "OpenGL 2.0 : GL_TEXTUREi must be bounded between [0;8)");
	GLCheck(glActiveTexture(GL_TEXTURE0 + Unit));

#else

	GLCheck(glActiveTextureARB(GL_TEXTURE0_ARB + Unit));

#endif // CA_PLATFORM_MOBILE    

    const GLTexture* pGLTexture = static_cast<const GLTexture*>(Texture);

    if (Texture)
    {
        GLCheck(glBindTexture(GL_TEXTURE_2D, pGLTexture->GetGLTexture()));
    }
    else
    {
        GLCheck(glBindTexture(GL_TEXTURE_2D, 0));
    }
}


/////////////////////////////////////////////////////////////
/// Crée une nouvelle texture
///
/// \param Size :   Taille de la texture
/// \param Format : Format de pixel de la texture
/// \param Flags :  Options de création
///
/// \return Pointeur sur la texture créée
///
////////////////////////////////////////////////////////////
ITextureBase* GLRenderer::CreateTexture(
	const Vector2I& Size, 
	const PixelFormat::TPixelFormat Format,
	const unsigned char *data_,
	const unsigned long Flags) const
{
    // Génération de la texture
    unsigned int Texture;
    GLCheck(glGenTextures(1, &Texture));

    // Activation de la texture
    GLCheck(glBindTexture(GL_TEXTURE_2D, Texture));

	SetTextureWrap(Flags);
	SetTextureFilter(Flags);
	SetTextureAnisotropic(Flags);

    // Détermination du nombre de niveaux de mipmapping
    int NbMipmaps = Flags & TEX_NOMIPMAP ? 0 : GetNbMipLevels(Size.x, Size.y);

#if CA_PLATFORM_DESKTOP

    GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, NbMipmaps));

    // S'il y a plusieurs niveaux de mipmaps et si le système le supporte, on active la génération hardware des mipmaps
    if ((NbMipmaps > 0) && (HasCapability(Capability::HardwareMipmapping)))
        GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE));

#endif //  CA_PLATFORM_DESKTOP

    // Allocation de la mémoire pour tous les niveaux de mipmapping
    int Width  = Size.x;
    int Height = Size.y;

	//in OpenGL ES 2.0, mandatory => Internal == Format
	//do a software conversion
	GLCheck(glTexImage2D(
		GL_TEXTURE_2D, 0, 
		GLEnum::Get(Format).Internal, 
		Width, Height, 0, 
		GLEnum::Get(Format).Format, 
		GLEnum::Get(Format).Type, 
		data_));

    // Désactivation de la texture
    GLCheck(glBindTexture(GL_TEXTURE_2D, 0));

	CA_TRACE("OpenGL texture created (id=%d)\n", Texture);

	return NEW_AO GLTexture(Size, Format, NbMipmaps > 0, HasCapability(Capability::HardwareMipmapping), Texture, data_);
}

/**
 * 
 */
void GLRenderer::SetTextureWrap(const unsigned long Flags) const
{
	if (Flags & TEX_CLAMP )
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	}
	else if (Flags & TEX_BORDER )
	{
#if CA_PLATFORM_DESKTOP
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
#else
		CA_WARN("TEX_BORDER not supported with mobile platform\n");
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
#endif
	}
	else if (Flags & TEX_MIRROR )
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );			
	}
	else if (Flags & TEX_REPEAT )
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );			
	}
	else if (Flags & TEX_MIRROR_ONCE )
	{
#if CA_PLATFORM_DESKTOP
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE );
#else
		CA_WARN("TEX_MIRROR_ONCE not supported with mobile platform\n");
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
#endif			
	}
}

/**
 * 
 */
void GLRenderer::SetTextureFilter(const unsigned long Flags) const
{
	if (Flags & TEX_FILTER_0 )
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	}
	else if (Flags & TEX_FILTER_1 )
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );		
	}
	else if (Flags & TEX_FILTER_2 )
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );		
	}
	else if (Flags & TEX_FILTER_3 )
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );			
	}
}

/**
 * 
 */
void GLRenderer::SetTextureAnisotropic(const unsigned long Flags) const
{
	/*static float texture_max_anisotropy = 0.0f;

	if( !texture_max_anisotropy ) glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,
		&texture_max_anisotropy );

	float value = CLAMP(anisotropic_filter,
		0.0f,
		texture_max_anisotropy);

	glTexParameterf( texture->target,
		GL_TEXTURE_MAX_ANISOTROPY_EXT,
		anisotropic_filter);*/

	GLfloat value = 1.0f;

	/*if (Flags & TEX_ANISOTROPY_1 )
	{
		value = 1.0f;
	}
	else */if (Flags & TEX_ANISOTROPY_2)
	{
		value = 2.0f;
	}
	else if (Flags & TEX_ANISOTROPY_4)
	{
		value = 4.0f;
	}
	else if (Flags & TEX_ANISOTROPY_8)
	{
		value = 8.0f;
	}
	else if (Flags & TEX_ANISOTROPY_16)
	{
		value = 16.0f;
	}

	GLCheck(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, value));
}


/////////////////////////////////////////////////////////////
/// Paramètre l'alpha-blending
///
/// \param Src :  Paramètre source
/// \param Dest : Paramètre destination
///
////////////////////////////////////////////////////////////
void GLRenderer::SetupAlphaBlending(Blend::TBlend Src, Blend::TBlend Dest) const
{
    GLCheck(glBlendFunc(GLEnum::Get(Src), GLEnum::Get(Dest)));
}

/**
 * Used if separate alpha blend
 */
void GLRenderer::SetupAlphaBlending(Blend::TBlend Src, Blend::TBlend SrcAlpha, Blend::TBlend Dest, Blend::TBlend DestAlpha) const
{
	GLCheck(glBlendFuncSeparate(GLEnum::Get(Src), GLEnum::Get(SrcAlpha), GLEnum::Get(Dest), GLEnum::Get(DestAlpha)));
}


#if CA_PLATFORM_DESKTOP

/////////////////////////////////////////////////////////////
/// Paramètre les opérations d'une unité de texture
///
/// \param Unit :     Unité de texture
/// \param Op :       Opérateur
/// \param Arg1 :     Argument 1
/// \param Arg2 :     Argument 2
/// \param Constant : Constante, dans le cas où un argument est TXA_CONSTANT
///
////////////////////////////////////////////////////////////
void GLRenderer::SetupTextureUnit(unsigned int Unit, TextureOperation::TTextureOp Op, TTextureArg Arg1, TTextureArg Arg2, const CColor& Constant) const
{
    // Activation de l'unité de texture à paramétrer
    //glEnable(GL_TEXTURE_2D);
    GLCheck(glActiveTextureARB(GL_TEXTURE0_ARB + Unit));
    GLCheck(glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT));

    // Opérateur et arguments
    if (Op < TextureOperation::AlphaFirstArg)
    {
		GLCheck(glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GLEnum::Get(Op)));
		GLCheck(glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GLEnum::Get(Arg1)));
		GLCheck(glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GLEnum::Get(Arg2)));
        GLCheck(glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_EXT, GL_SRC_COLOR));
        GLCheck(glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, GL_SRC_COLOR));
    }
    else
    {
		GLCheck(glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GLEnum::Get(Op)));
		GLCheck(glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, GLEnum::Get(Arg1)));
		GLCheck(glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT, GLEnum::Get(Arg2)));
        GLCheck(glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA_EXT, GL_SRC_ALPHA));
        GLCheck(glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA_EXT, GL_SRC_ALPHA));
    }

    // Constante
    if ((Arg1 == TXA_CONSTANT) || (Arg2 == TXA_CONSTANT))
    {
        float Color[4];
        Constant.ToFloat(Color);
        GLCheck(glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, Color));
    }
}

#endif // CA_PLATFORM_DESKTOP

//----------------------------------------------------------
// define the scissor box
//----------------------------------------------------------
void GLRenderer::SetScissorRect(const CRectangle* pRect_)
{
	GLCheck(glScissor(
		pRect_->Left(), pRect_->Top(),
		pRect_->Width(), pRect_->Height()) );
}

//----------------------------------------------------------
// Get the scissor box
//----------------------------------------------------------
void GLRenderer::GetScissorRect(CRectangle *pRect_) const
{
	CA_ASSERT(pRect_ != nullptr, "GLRenderer::GetScissorRect() : rectangle is nullptr");

	GLint rect[4];
	GLCheck(glGetIntegerv(GL_SCISSOR_BOX, rect));
	
	pRect_->Set(rect[0], rect[1], rect[2], rect[3]);
}

/////////////////////////////////////////////////////////////
/// Active / désactive un paramètre de rendu
///
/// \param Param : Paramètre de rendu
/// \param Value : Valeur (actif / inactif)
///
////////////////////////////////////////////////////////////
void GLRenderer::Enable(RenderParameter::TRenderParameter Param, unsigned int Value) const
{
	GLint sfail, dpfail, dppass, func, ref, mask;

	switch (Param)
	{
	case RenderParameter::CullFace:
		if (Value == RenderParameter::CULLFACE_NONE)
		{
			GLCheck(glDisable(GL_CULL_FACE));
		}
		else
		{
			GLCheck(glEnable(GL_CULL_FACE));

			Value = (Value == RenderParameter::CULLFACE_CW ? GL_CW : GL_CCW);
			GLCheck(glFrontFace(Value));

			//glCullFace(); GL_FRONT, GL_BACK, or GL_FRONT_AND_BACK
			//
		}
		
		return;
	}

	switch (Param)
	{
        case RenderParameter::ZWrite :
            GLCheck(glDepthMask(static_cast<GLboolean>(Value)));
            break;

#if CA_PLATFORM_DESKTOP

		case RenderParameter::FillMode :
			GLCheck(glPolygonMode(GL_FRONT_AND_BACK, GLEnum::Get(static_cast<RenderParameter::TFillMode>(Value) )) );
			break;

#endif // CA_PLATFORM_DESKTOP

		case RenderParameter::StencilFail :
			Value = GLEnum::Get(static_cast<RenderParameter::TStencilOperation>(Value));			
			GLCheck(glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &dpfail));
			GLCheck(glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &dppass));
			GLCheck(glStencilOp(Value, dpfail, dppass));
			break;

		case RenderParameter::StencilZFail :
			Value = GLEnum::Get(static_cast<RenderParameter::TStencilOperation>(Value));
			GLCheck(glGetIntegerv(GL_STENCIL_FAIL, &sfail));
			GLCheck(glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &dppass));
			GLCheck(glStencilOp(sfail, Value, dppass));
			break;

		case RenderParameter::StencilPass :	
			Value = GLEnum::Get(static_cast<RenderParameter::TStencilOperation>(Value));
			GLCheck(glGetIntegerv(GL_STENCIL_FAIL, &sfail));
			GLCheck(glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &dpfail));
			GLCheck(glStencilOp(sfail, dpfail, Value));
			break;

		case RenderParameter::StencilMask:
			GLCheck(glStencilMask(Value));
			break;

		case RenderParameter::StencilFunc :
			Value = GLEnum::Get(static_cast<TCompareFunction>(Value));
			GLCheck(glGetIntegerv(GL_STENCIL_REF, &ref));
			GLCheck(glGetIntegerv(GL_STENCIL_VALUE_MASK, &mask));			
			GLCheck(glStencilFunc(Value, ref, mask));
			break;

		case RenderParameter::StencilRef :
			GLCheck(glGetIntegerv(GL_STENCIL_FUNC, &func));
			GLCheck(glGetIntegerv(GL_STENCIL_VALUE_MASK, &mask));
			GLCheck(glStencilFunc(func, Value, mask));
			break;

		/*case RenderParameter::StencilWriteMask :
			Value = GLEnum::Get(static_cast<TCompareFunction>(Value));
			//glStencilFunc(GLenum func,  GLint ref,  GLuint mask);
			break;*/

        default :
            if (Value)
			{
                GLCheck(glEnable(GLEnum::Get(Param)));
			}
            else
			{
                GLCheck(glDisable(GLEnum::Get(Param)));
			}
    }
}


////////////////////////////////////////////////////////////
/// Crée un shader à partir d'un programme Cg
///
/// \param Program : Programme Cg
/// \param Type :    Type du shader
///
/// \return Shader créé et chargé
///
////////////////////////////////////////////////////////////
IShaderBase* GLRenderer::CreateShader(IFile *pFile_) const
{
	return NEW_AO GLShader(pFile_);
}


/**
 * 
 */
IEffect *GLRenderer::CreateEffectFromShader(IShaderBase *pShader_) const
{
	GLShader *pGLShader = dynamic_cast<GLShader *>(pShader_);

	CA_ASSERT(pGLShader != nullptr, "GLRenderer::CreateEffectFromShader() : IShaderBase is not a GLShader");

	GLEffect *pEffect = NEW_AO GLEffect();
	pEffect->AddPass(pGLShader);
	return pEffect;
}

/**
 * 
 */
TextureTarget* GLRenderer::CreateTextureTarget(const Vector2I &size, PixelFormat::TPixelFormat format )
{
	return NEW_AO GLRenderTargetTexture(size, format);
}

/**
 * 
 */
void GLRenderer::SetClearColor( CColor color_ )
{
	IRenderer::SetClearColor(color_);

	float color[4];
	color_.ToFloat(color);
	GLCheck(glClearColor(color[0], color[1], color[2], color[3]));
}

/**
 * 
 */
void GLRenderer::Resize(unsigned int width_, unsigned height_)
{
	CA_UNUSED(width_, height_)
	//TODO : used Window in the class Game in order to retrieve width & height
	//GLCheck(glViewport(0, 0, width_, height_));
}

/**
 * 
 */
Viewport GLRenderer::GetViewport() const
{
	GLint glVp[4]; 
	GLCheck(glGetIntegerv (GL_VIEWPORT, glVp));

	Viewport vp;
	vp.X(static_cast<float>(glVp[0]));
	vp.Y(static_cast<float>(glVp[1]));
	vp.Width(static_cast<float>(glVp[2]));
	vp.Height(static_cast<float>(glVp[3]));

	return vp;
}

/**
 * 
 */
void GLRenderer::SetViewport(const Viewport &vp_)
{
	//CA_TRACE("Viewport %f %f %f %f\n", 
	//	vp_.X(), vp_.Y(), vp_.Width(), vp_.Height());

	GLCheck(glViewport(
		static_cast<GLint>(vp_.X()), 
		static_cast<GLint>(vp_.Y()), 
		static_cast<GLsizei>(vp_.Width()), 
		static_cast<GLsizei>(vp_.Height()) ));
}

} // namespace CasaEngine
