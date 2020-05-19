#include "Base.h"
#include "Texture.h"
#include "Log\LogManager.h"
#include "IO\IFile.h"
#include "Resources\MediaManager.h"
#include "bx\string.h"
#include "bimg\decode.h"

#include "Game/Game.h"

namespace CasaEngine
{

	//create only one allocator
	bx::AllocatorI* getDefaultAllocator()
	{
		static bx::DefaultAllocator s_allocator;
		return &s_allocator;
	}

	static void imageReleaseCb(void* _ptr, void* _userData)
	{
		bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)_userData;
		bimg::imageFree(imageContainer);
	}

	/**
	 *
	 */
	Texture* Texture::loadTexture(const char* pFileName_, uint32_t _flags, uint8_t _skip, bgfx::TextureInfo* _info)
	{
		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

		bgfx::TextureHandle h = BGFX_INVALID_HANDLE;
		IFile* pFile = Game::Instance().GetMediaManager().FindMedia(pFileName_, true);

		if (pFile == nullptr)
		{
			CA_ERROR("Failed to load %s.", pFileName_);
			return nullptr;
		}

		void* data = pFile->GetBuffer();

		if (NULL != data)
		{
			bimg::ImageContainer* imageContainer = bimg::imageParse(getDefaultAllocator(), data, pFile->GetBufferLength());

			if (NULL != imageContainer)
			{
				/*if (NULL != _orientation)
				{
					*_orientation = imageContainer->m_orientation;
				}*/

				const bgfx::Memory* mem = bgfx::makeRef(
					imageContainer->m_data
					, imageContainer->m_size
					, imageReleaseCb
					, imageContainer
				);

				if (imageContainer->m_cubeMap)
				{
					handle = bgfx::createTextureCube(
						uint16_t(imageContainer->m_width)
						, 1 < imageContainer->m_numMips
						, imageContainer->m_numLayers
						, bgfx::TextureFormat::Enum(imageContainer->m_format)
						, _flags
						, mem
					);
				}
				else if (1 < imageContainer->m_depth)
				{
					handle = bgfx::createTexture3D(
						uint16_t(imageContainer->m_width)
						, uint16_t(imageContainer->m_height)
						, uint16_t(imageContainer->m_depth)
						, 1 < imageContainer->m_numMips
						, bgfx::TextureFormat::Enum(imageContainer->m_format)
						, _flags
						, mem
					);
				}
				else if (bgfx::isTextureValid(0, false, imageContainer->m_numLayers, bgfx::TextureFormat::Enum(imageContainer->m_format), _flags))
				{
					handle = bgfx::createTexture2D(
						uint16_t(imageContainer->m_width)
						, uint16_t(imageContainer->m_height)
						, 1 < imageContainer->m_numMips
						, imageContainer->m_numLayers
						, bgfx::TextureFormat::Enum(imageContainer->m_format)
						, _flags
						, mem
					);
				}

				if (bgfx::isValid(handle))
				{
					bgfx::setName(handle, pFile->Fullname().c_str());
				}

				if (nullptr == _info)
				{
					_info = NEW_AO bgfx::TextureInfo();
				}

				bgfx::calcTextureSize(
					*_info
					, uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, uint16_t(imageContainer->m_depth)
					, imageContainer->m_cubeMap
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
				);
			}
		}

		DELETE_AO pFile;
		return NEW_AO Texture(handle, _info);
	}

	/**
	 *
	 */
	Texture* Texture::createTexture(const unsigned int width_, const unsigned int height_, const bgfx::TextureFormat::Enum format_,
		const bgfx::Memory* pData_, const unsigned long flags_, bgfx::TextureInfo* info_)
	{
		bgfx::TextureHandle handle = bgfx::createTexture2D(uint16_t(width_), uint16_t(height_), true, 1,
			format_, uint32_t(flags_), pData_);

		if (NULL != info_)
		{
			bgfx::calcTextureSize(*info_
				, uint16_t(width_)
				, uint16_t(height_)
				, 0
				, false
				, true
				, 1
				, format_
			);
		}

		return NEW_AO Texture(handle, info_);
	}

	/**
	 *
	 */
	Texture::Texture(bgfx::TextureHandle handle_, bgfx::TextureInfo* pInfo_ /*= nullptr*/)
	{
		m_Handle = handle_;
		m_pTextureInfo = pInfo_;
	}

	/**
	 *
	 */
	Texture::~Texture()
	{
		bgfx::destroy(m_Handle);
	}

	/**
	 *
	 */
	bgfx::TextureInfo* Texture::TextureInfo() const
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

}
