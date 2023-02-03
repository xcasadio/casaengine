#ifndef TEXTURE_H
#define TEXTURE_H

#include "CA_Export.h"

#include "IO/IFile.h"
#include <bgfx/bgfx.h>
#include <map>

namespace CasaEngine
{
	class CA_EXPORT Texture
	{
	public:
		static Texture* loadTexture(IFile* pFile, uint32_t _flags = BGFX_TEXTURE_NONE, uint8_t _skip = 0);
		static Texture* createTexture(unsigned int width_, unsigned int height_, bgfx::TextureFormat::Enum format_,
			const bgfx::Memory* pData_, unsigned long flags_ = BGFX_TEXTURE_NONE, bgfx::TextureInfo* info_ = nullptr);
	private:
		static std::map<std::string, Texture*> _textureCache;

	public:
		Texture(bgfx::TextureHandle handle_, bgfx::TextureInfo* info_ = nullptr);
		virtual ~Texture();

		bgfx::TextureHandle Handle() const;
		bgfx::TextureInfo* TextureInfo() const;

	private:
		bgfx::TextureInfo* m_pTextureInfo;
		bgfx::TextureHandle m_Handle;
	};
}

#endif
