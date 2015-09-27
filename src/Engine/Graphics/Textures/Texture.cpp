#include "Base.h"
#include "Texture.h"
#include "Log\LogManager.h"
#include "IO\IFile.h"
#include "Resources\MediaManager.h"
#include "bx\string.h"

// #define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace CasaEngine
{

/**
 * 
 */
Texture *Texture::loadTexture(const char *pFileName_, uint32_t _flags, uint8_t _skip, bgfx::TextureInfo* _info)
{
	bgfx::TextureHandle h = BGFX_INVALID_HANDLE;
	IFile *pFile = MediaManager::Instance().FindMedia(pFileName_, true);

	if (pFile == nullptr) 
	{
		return nullptr;
	}

	const bgfx::Memory *pMem = bgfx::makeRef((uint8_t *)pFile->GetBuffer(), pFile->GetBufferLength());

	if (NULL != bx::stristr(pFileName_, ".dds")
		||  NULL != bx::stristr(pFileName_, ".pvr")
		||  NULL != bx::stristr(pFileName_, ".ktx") )
	{
		h = bgfx::createTexture(pMem, _flags, _skip, _info);
		return NEW_AO Texture(h, _info);
	}

	bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

	uint32_t size = pMem->size;
	void* data = const_cast<bgfx::Memory *>(pMem);

	if (NULL != data)
	{
		int width  = 0;
		int height = 0;
		int comp   = 0;

		uint8_t* img = NULL;
		img = stbi_load_from_memory((uint8_t*)data, size, &width, &height, &comp, 4);

		if (NULL != img)
		{
			handle = bgfx::createTexture2D(uint16_t(width), uint16_t(height), 1
				, bgfx::TextureFormat::RGBA8
				, _flags
				, bgfx::copy(img, width*height*4)
				);

			free(img);

			if (NULL != _info)
			{
				bgfx::calcTextureSize(*_info
					, uint16_t(width)
					, uint16_t(height)
					, 0
					, false
					, 1
					, bgfx::TextureFormat::RGBA8
					);
			}
		}
	}
	else
	{
		CA_ERROR("Failed to load %s.", pFileName_);
	}

	return NEW_AO Texture(h, _info);
}

/**
 * 
 */
Texture *Texture::createTexture(const unsigned int width_, const unsigned int height_, const bgfx::TextureFormat::Enum format_, 
	const bgfx::Memory *pData_, const unsigned long flags_, bgfx::TextureInfo* info_)
{
	bgfx::TextureHandle handle = bgfx::createTexture2D(uint16_t(width_), uint16_t(height_), 1, 
		format_ , uint32_t(flags_) , pData_);

	if (NULL != info_)
	{
		bgfx::calcTextureSize(*info_
			, uint16_t(width_)
			, uint16_t(height_)
			, 0
			, false
			, 1
			, format_
			);
	}

	return NEW_AO Texture(handle, info_);
}

/**
 * 
 */
Texture::Texture(bgfx::TextureHandle handle_, bgfx::TextureInfo *pInfo_ /*= nullptr*/)
{
	m_Handle = handle_;
	m_pTextureInfo = pInfo_;
}

/**
 * 
 */
Texture::~Texture()
{
	bgfx::destroyTexture(m_Handle);
}

/**
 * 
 */
bgfx::TextureInfo * Texture::TextureInfo() const
{
	return m_pTextureInfo;
}

/**
 * 
 */
bgfx::TextureHandle Texture::Handle() const
{
	return m_Handle;
}

} // namespace CasaEngine
