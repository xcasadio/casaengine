#include "Graphics\Renderer\Enums.h"
#include "Maths\Vector2.h"
#include "Graphics\RenderTarget.h"
#include "Graphics\TextureTarget.h"
#include "GLTexture.h"

#ifndef GLRENDERTARGET_H
#define GLRENDERTARGET_H


namespace CasaEngine
{
	/**
	 * 
	 */
    class GLRenderTargetTexture : public TextureTarget
    {
    public :

        /**
         * 
         */
        GLRenderTargetTexture(const Vector2I& Size, PixelFormat::TPixelFormat Format);

		~GLRenderTargetTexture();

        /**
         * 
         */
        GLuint GetGLTexture() const;

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
		void CheckFramebufferStatus();

		/**
		 * 
		 */
		Texture *GetTexture();
		
		/**
		 * 
		 */
		bool IsImageryCache() const;

		/**
		 * 
		 */
		bool IsRenderingInverted() const;

    private :
        //unsigned int m_Texture;
		PixelFormat::TPixelFormat m_Format;
		GLuint m_GLFrameBuffer, m_GLTexture, m_GLOldFrameBuffer;
		GLTexture *m_pGLTexture;
		Texture *m_pTexture;
    };

} // namespace CasaEngine


#endif // GLRENDERTARGET_H
