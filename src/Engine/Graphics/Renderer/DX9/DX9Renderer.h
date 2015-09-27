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

#ifndef DX9RENDERER_H
#define DX9RENDERER_H

//==========================================================
// En-têtes
//==========================================================
#include "d3d9.h"
#include "d3dx9.h"
#include <vector>

#include "Graphics/Renderer/Renderer.h"
#include "Singleton.h"
#include "SmartPtr.h"
#include "Maths/Matrix4.h"

#include "SFML/System/NonCopyable.hpp"
#include "Graphics/Effects/IEffect.h"
#include "Graphics/Effects/ShaderBase.h"
#include "IO/IFile.h"
#include "Graphics/Viewport.h"
#include "Graphics/TextureTarget.h"
#include "SFML/Window/Window.hpp"


namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    /// Renderer DirectX9
    /////////////////////////////////////////////////////////////
    class DX9Renderer : public IRenderer, 
		public CSingleton<DX9Renderer>
    {
    MAKE_SINGLETON(DX9Renderer)

    public :

        //----------------------------------------------------------
        // Renvoie une description du renderer courant
        //----------------------------------------------------------
        std::string GetRendererDesc() const;

		/**
		 * Returns the extension of the shader file (.hlsl)
		 */
		const char * DX9Renderer::GetShaderFileExtension() const;

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

		//----------------------------------------------------------
		// Affiche des primitives
		//----------------------------------------------------------
		void DrawPrimitivesInstanced(PrimitiveType::TPrimitiveType Type, unsigned long FirstVertex, unsigned long Count, unsigned long nbElt_) const;

		//----------------------------------------------------------
		// Affiche des primitives indicées
		//----------------------------------------------------------
		void DrawIndexedPrimitivesInstanced(PrimitiveType::TPrimitiveType Type, unsigned long FirstIndex, unsigned long Count, unsigned long nbElt_) const;

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
        void SetupTextureUnit(unsigned int Unit, TextureOperation::TTextureOp Op, TTextureArg Arg1, TTextureArg Arg2 = TXA_DIFFUSE, const CColor& Constant = 0x00) const;

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
        /// 
        //----------------------------------------------------------
        IShaderBase* CreateShader(IFile *pFile_) const;

		/**
		 * 
		 */
		IEffect* CreateEffectFromShader(IShaderBase *pShader) const;

		/**
		 * 
		 */
		TextureTarget* CreateTextureTarget(const Vector2I &size, PixelFormat::TPixelFormat format);

		//TODO : delete
		IDirect3DDevice9* GetDevice() const;

		/**
		 * 
		 */
		Viewport GetViewport() const;

		/**
		 * 
		 */
		void SetViewport(const Viewport &vp_);

    protected :

        //----------------------------------------------------------
        // Initialise l'API
        //----------------------------------------------------------
        void Setup(sf::Window *pWindow_);

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
        DX9Renderer();

        //----------------------------------------------------------
        // Destructeur
        //----------------------------------------------------------
        ~DX9Renderer();

        //----------------------------------------------------------
        // Indique si un format de pixel donné est supporté
        //----------------------------------------------------------
        bool CheckFormat(D3DFORMAT Format, D3DRESOURCETYPE ResourceType, unsigned long Usage = 0);


        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        SmartPtr<IDirect3D9, CResourceCOM>       m_Direct3D;    ///< Objet D3D
        SmartPtr<IDirect3DDevice9, CResourceCOM> m_Device;      ///< Device D3D
		unsigned long                            m_MinVertex;   ///< Sauvegarde de l'indice min des prochains vertices à rendre
        unsigned long                            m_VertexCount; ///< Sauvegarde du nombre des prochains vertices à rendre
        std::vector<Matrix4>                     m_Matrices[6]; ///< Piles de matrices
    };
	
#include "DX9Renderer.inl"

} // namespace CasaEngine


#endif // DX9RENDERER_H
