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

#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "SystemPlatform.h"

#if CA_PLATFORM_ANDROID

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else

#include <windows.h>
#include "SFML/System/NonCopyable.hpp"

#include <GL/glew.h>
#include <gl/gl.h>
#include "Extensions/glext.h"

#endif // #if CA_PLATFORM_ANDROID

#include <vector>

#include "Graphics/Renderer/Renderer.h"
#include "Singleton.h"
#include "GLException.h"
#include "Graphics/Vertices/DeclarationElement.h"

#include "Graphics/Effects/IEffect.h"
#include "Graphics/Effects/Shader.h"
#include "IO/IFile.h"
#include "Graphics/Viewport.h"
#include "Graphics/TextureTarget.h"
#include "SFML/Window/Window.hpp"

namespace CasaEngine
{
    class GLDeclaration;

    /////////////////////////////////////////////////////////////
    // Renderer OpenGL
    /////////////////////////////////////////////////////////////
    class GLRenderer : public IRenderer, public CSingleton<GLRenderer>
    {
    MAKE_SINGLETON(GLRenderer)

    public :

        //----------------------------------------------------------
        // Renvoie une description du renderer courant
        //----------------------------------------------------------
        std::string GetRendererDesc() const;

		/**
		 * Returns the extension of the shader file
		 */
		const char * GetShaderFileExtension() const;

		/**
		 * 
		 */
		void Resize(unsigned int width_, unsigned height_);

        //----------------------------------------------------------
        // Démarre le rendu de la scène
        //----------------------------------------------------------
        void BeginScene();

        //----------------------------------------------------------
        // Termine le rendu de la scène
        //----------------------------------------------------------
        void EndScene();

		/**
		 * 
		 */
		void Clear(unsigned int flags);

        //----------------------------------------------------------
        // Change le vertex buffer courant
        //----------------------------------------------------------
        void SetVB(unsigned int Stream, const IBufferBase* Buffer, unsigned long Stride, unsigned long MinVertex, unsigned long MaxVertex);

        //----------------------------------------------------------
        // Change le index buffer courant
        //----------------------------------------------------------
        void SetIB(const IBufferBase* Buffer, unsigned long Stride);

        //----------------------------------------------------------
        // Change la déclaration de vertex courante
        //----------------------------------------------------------
        void SetDeclaration(const IDeclaration* Declaration);

        //----------------------------------------------------------
        // Affiche des primitives
        //----------------------------------------------------------
        void DrawPrimitives(PrimitiveType::TPrimitiveType Type, unsigned long FirstVertex, unsigned long Count) const;

        //----------------------------------------------------------
        // Affiche des primitives indicées
        //----------------------------------------------------------
        void DrawIndexedPrimitives(PrimitiveType::TPrimitiveType Type, unsigned long FirstIndex, unsigned long Count) const;

#if CA_PLATFORM_DESKTOP

		//----------------------------------------------------------
		// Affiche des primitives
		//----------------------------------------------------------
		void DrawPrimitivesInstanced(PrimitiveType::TPrimitiveType Type, unsigned long FirstVertex, unsigned long Count, unsigned long nbElt_) const;

		//----------------------------------------------------------
		// Affiche des primitives indicées
		//----------------------------------------------------------
		void DrawIndexedPrimitivesInstanced(PrimitiveType::TPrimitiveType Type, unsigned long FirstIndex, unsigned long Count, unsigned long nbElt_) const;

#endif // CA_PLATFORM_DESKTOP

        //----------------------------------------------------------
        // Empile la matrice courante
        //----------------------------------------------------------
        /*virtual void PushMatrix(MatrixType::TMatrixType Type);

        //----------------------------------------------------------
        // Dépile la matrice en haut de la pile
        //----------------------------------------------------------
        virtual void PopMatrix(MatrixType::TMatrixType Type);

        //----------------------------------------------------------
        // Charge une matrice
        //----------------------------------------------------------
        virtual void LoadMatrix(MatrixType::TMatrixType Type, const Matrix4& Matrix);

        //----------------------------------------------------------
        // Charge une matrice en la multipliant avec la précédente
        //----------------------------------------------------------
        virtual void LoadMatrixMult(MatrixType::TMatrixType Type, const Matrix4& Matrix);

        //----------------------------------------------------------
        // Récupère la matrice courante
        //----------------------------------------------------------
        virtual void GetMatrix(MatrixType::TMatrixType Type, Matrix4& Matrix) const;
		*/
        //----------------------------------------------------------
        // Convertit une couleur dans le format pris en charge par l'API
        //----------------------------------------------------------
        unsigned long ConvertColor(const CColor& Color) const;

        //----------------------------------------------------------
        // Change une texture
        //----------------------------------------------------------
        void SetTexture(unsigned int Unit, const ITextureBase* Texture) const;

        //----------------------------------------------------------
        // Crée une texture à partir d'une image
        //----------------------------------------------------------
		ITextureBase* CreateTexture(const Vector2I& Size, 
			const PixelFormat::TPixelFormat Format,
			const unsigned char *data_ = nullptr,
			const unsigned long Flags = 0) const;

		/**
		 * A texture must be bind before call this function
		 */
		void SetTextureWrap(const unsigned long Flags) const;

		/**
		 * A texture must be bind before call this function
		 */
		void SetTextureFilter(const unsigned long Flags) const;

		/**
		 * A texture must be bind before call this function
		 */
		void SetTextureAnisotropic(const unsigned long Flags) const;

        //----------------------------------------------------------
        // Paramètre l'alpha-blending
        //----------------------------------------------------------
        void SetupAlphaBlending(Blend::TBlend Src, Blend::TBlend Dest) const;

		/**
		 * Used if separate alpha blend
		 */
		void SetupAlphaBlending(Blend::TBlend Src, Blend::TBlend SrcAlpha, Blend::TBlend Dest, Blend::TBlend DestAlpha) const;

        //----------------------------------------------------------
        // Paramètre les opérations d'une unité de texture
        //----------------------------------------------------------
#if CA_PLATFORM_DESKTOP

		void SetupTextureUnit(unsigned int Unit, TextureOperation::TTextureOp Op, TTextureArg Arg1, TTextureArg Arg2 = TXA_DIFFUSE, const CColor& Constant = 0x00) const;

#endif

		//----------------------------------------------------------
		// define the scissor box
		//----------------------------------------------------------
		void SetScissorRect(const CRectangle* pRect_);

		//----------------------------------------------------------
		// Get the scissor box
		//----------------------------------------------------------
		void GetScissorRect(CRectangle *pRect_) const;

        //----------------------------------------------------------
        // Active / désactive un paramètre de rendu
        //----------------------------------------------------------
        void Enable(RenderParameter::TRenderParameter Param, unsigned int Value) const;

        //----------------------------------------------------------
        /// Crée un shader à partir d'un programme Cg
        //----------------------------------------------------------
        IShaderBase* CreateShader(IFile *pFile_) const;

		/**
		 * 
		 */
		IEffect* CreateEffectFromFile(std::string fileName_) const;

		/**
		 * 
		 */
		IEffect* CreateEffectFromShader(IShaderBase *pShader) const;

		/**
		 * 
		 */
		TextureTarget* CreateTextureTarget(const Vector2I &size, PixelFormat::TPixelFormat format );

		/**
		 * 
		 */
		void SetClearColor(CColor color_);

		/**
		 * 
		 */
		Viewport GetViewport() const;

		/**
		 * 
		 */
		void SetViewport(const Viewport &vp_);

    public :

#if CA_PLATFORM_WINDOWS

        //----------------------------------------------------------
        // Extensions OpenGL
        //----------------------------------------------------------
        static PFNGLBINDBUFFERARBPROC               glBindBufferARB;
        static PFNGLDELETEBUFFERSARBPROC            glDeleteBuffersARB;
        static PFNGLGENBUFFERSARBPROC               glGenBuffersARB;
        static PFNGLBUFFERDATAARBPROC               glBufferDataARB;
        static PFNGLBUFFERSUBDATAARBPROC            glBufferSubDataARB;
        static PFNGLGETBUFFERSUBDATAARBPROC         glGetBufferSubDataARB;
        static PFNGLMAPBUFFERARBPROC                glMapBufferARB;
        static PFNGLUNMAPBUFFERARBPROC              glUnmapBufferARB;
        static PFNGLACTIVETEXTUREARBPROC            glActiveTextureARB;
        static PFNGLCLIENTACTIVETEXTUREARBPROC      glClientActiveTextureARB;
        static PFNGLCOMPRESSEDTEXIMAGE2DARBPROC     glCompressedTexImage2DARB;
        static PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC  glCompressedTexSubImage2DARB;
        static PFNGLGENPROGRAMSARBPROC              glGenProgramsARB;
        static PFNGLBINDPROGRAMARBPROC              glBindProgramARB;
        static PFNGLPROGRAMSTRINGARBPROC            glProgramStringARB;
        static PFNGLDELETEPROGRAMSARBPROC           glDeleteProgramsARB;
        static PFNGLPROGRAMLOCALPARAMETER4FVARBPROC glProgramLocalParameter4fvARB;
        static PFNGLCREATEPROGRAMOBJECTARBPROC      glCreateProgramObjectARB;
        static PFNGLCREATESHADEROBJECTARBPROC       glCreateShaderObjectARB;
        static PFNGLSHADERSOURCEARBPROC             glShaderSourceARB;
        static PFNGLCOMPILESHADERARBPROC            glCompileShaderARB;
        static PFNGLATTACHOBJECTARBPROC             glAttachObjectARB;
        static PFNGLLINKPROGRAMARBPROC              glLinkProgramARB;
        static PFNGLGETOBJECTPARAMETERIVARBPROC     glGetObjectParameterivARB;
        static PFNGLGETACTIVEUNIFORMARBPROC         glGetActiveUniformARB;
        static PFNGLGETUNIFORMLOCATIONARBPROC       glGetUniformLocationARB;
        static PFNGLUSEPROGRAMOBJECTARBPROC         glUseProgramObjectARB;
        static PFNGLUNIFORM4FARBPROC                glUniform4fARB;
        static PFNGLDELETEOBJECTARBPROC             glDeleteObjectARB;
        static PFNGLCOMBINERSTAGEPARAMETERFVNVPROC  glCombinerStageParameterfvNV;

#else
		
		static PFNGLMAPBUFFEROESPROC				glMapBufferOES;
		static PFNGLUNMAPBUFFEROESPROC				glUnmapBufferOES;

#endif // CA_PLATFORM_WINDOWS




    protected :

        //----------------------------------------------------------
        // Initialise l'API
        //----------------------------------------------------------
#if CA_PLATFORM_DESKTOP

        void Setup(sf::Window *pWindow_);

#else

		void Setup();

#endif // CA_PLATFORM_DESKTOP

        //----------------------------------------------------------
        // Vérifie les fonctionnalités supportées et met à jour la table des fonctionnalités
        //----------------------------------------------------------
        void CheckCaps();

        //----------------------------------------------------------
        // Crée un vertex buffer
        //----------------------------------------------------------
        IBufferBase* CreateVB(unsigned long Size, unsigned long Stride, unsigned long Flags) const;

        //----------------------------------------------------------
        // Crée un index buffer
        //----------------------------------------------------------
        IBufferBase* CreateIB(unsigned long Size, unsigned long Stride, unsigned long Flags) const;

        //----------------------------------------------------------
        // Crée une déclaration de vertex
        //----------------------------------------------------------
        IDeclaration* CreateDeclaration(const DeclarationElement::TDeclarationElement* Elements, std::size_t Count) const;

    private :

        //----------------------------------------------------------
        // Constructeur par défaut
        //----------------------------------------------------------
        GLRenderer();

        //----------------------------------------------------------
        // Destructeur
        //----------------------------------------------------------
        ~GLRenderer();

        //----------------------------------------------------------
        // Vérifie le support d'une extension
        //----------------------------------------------------------
        bool CheckExtension(const std::string& Extension) const;

		//----------------------------------------------------------
		// Charge les extensions OpenGL
		//----------------------------------------------------------
		void LoadExtensions();


#if CA_PLATFORM_DESKTOP
		sf::Window *m_pWindow;
		//HWND                   m_Hwnd;               ///< Handle du contrôle sur lequel faire le rendu
		//HDC                    m_Handle;             ///< Handle graphic du contrôle
		//HGLRC                  m_Context;            ///< Contexte de rendu

#endif // CA_PLATFORM_DESKTOP

        const GLDeclaration* m_CurrentDeclaration; ///< Declaration courante
        unsigned long          m_IndexStride;        ///< Taille courante des indices
        std::string            m_Extensions;         ///< Liste des extensions OpenGL supportées
    };

} // namespace CasaEngine


#endif // GLRENDERER_H
