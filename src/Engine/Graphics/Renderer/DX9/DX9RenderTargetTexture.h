
#ifndef DX9RENDERTARGET_H
#define DX9RENDERTARGET_H


#include "DX9Renderer.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/TextureTarget.h"
#include "Graphics/Textures/Texture.h"
#include "SmartPtr.h"
#include "DX9Texture.h"


namespace CasaEngine
{
	/**
	 *
	 */
    class DX9RenderTargetTexture : public TextureTarget
    {
    public :

		/**
		 *
		 */
        DX9RenderTargetTexture();

        /**
		 *
		 */
        DX9RenderTargetTexture(const Vector2I& Size, PixelFormat::TPixelFormat Format);

		/**
		 *
		 */
        ~DX9RenderTargetTexture();

        /**
		 *
		 */
        IDirect3DTexture9* GetDxTexture() const;

		/**
		 * 
		 */
		void Release();

		/**
		 *
		 */
		void Create(const Vector2I& Size, PixelFormat::TPixelFormat Format);

		/**
		 *
		 */
		void Activate();

		/**
		 *
		 */
		void Deactivate();

		/**
		 *
		 */
		Texture * GetTexture();
		
		/**
		 * 
		 */
		bool IsImageryCache() const;

		/**
		 * 
		 */
		bool IsRenderingInverted() const;

    private :
        //! Direct3D9 texture that's rendered to.
        LPDIRECT3DTEXTURE9 m_pDirect3DTexture9;
		//! Direct3D9 surface for the texture
		LPDIRECT3DSURFACE9 m_pSurface;
		//! we use this to wrap d_texture so it can be used by the core CEGUI lib.
		//Direct3D9Texture* d_CEGUITexture;
		//! colour surface that was in use before this target was activated.
		LPDIRECT3DSURFACE9 m_pPrevColourSurface;

		DX9Texture *m_pDX9Texture;
		Texture *m_pTexture;
    };

} // namespace CasaEngine


#endif // DX9RENDERTARGET_H
