#ifndef TEXTURE_H
#define TEXTURE_H

#include "CA_Export.h"

#include "Resources/Resource.h"
#include <bgfx/bgfx.h>

namespace CasaEngine
{
    /**
     * 
     */
    class CA_EXPORT Texture :
		public IResource
    {
    public :

		/**
		 * 
		 */
		static Texture *loadTexture(const char *pFileName_, uint32_t _flags = BGFX_TEXTURE_NONE, uint8_t _skip = 0, bgfx::TextureInfo* _info = nullptr);

		/**
		 * 
		 */
		static Texture *createTexture(const unsigned int width_, const unsigned int height_, const bgfx::TextureFormat::Enum format_, 
			const bgfx::Memory *pData_, const unsigned long flags_ = BGFX_TEXTURE_NONE, bgfx::TextureInfo* info_ = nullptr);

	public:

        /**
         * 
         */
        Texture(bgfx::TextureHandle handle_, bgfx::TextureInfo *info_ = nullptr);

		/**
		 * 
		 */
        virtual ~Texture();

		/**
		 * 
		 */
		bgfx::TextureHandle Handle() const;

		/**
		 * 
		 */
		bgfx::TextureInfo *TextureInfo() const;
    private :
		bgfx::TextureInfo *m_pTextureInfo;
		bgfx::TextureHandle m_Handle;
	};

}

#endif
