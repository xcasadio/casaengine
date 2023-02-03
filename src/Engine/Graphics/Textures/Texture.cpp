#include "Base.h"
#include "Texture.h"
#include "Log/LogManager.h"
#include "Resources/MediaManager.h"
#include "bx/string.h"
#include "bimg/decode.h"

namespace CasaEngine
{
	std::map<std::string, Texture*> Texture::_textureCache;

	bx::AllocatorI* getDefaultAllocator()
	{
		static bx::DefaultAllocator s_allocator;
		return &s_allocator;
	}

	static void imageReleaseCb(void* _ptr, void* _userData)
	{
		auto imageContainer = static_cast<bimg::ImageContainer*>(_userData);
		imageFree(imageContainer);
	}

	Texture* Texture::loadTexture(IFile* pFile, uint32_t _flags, uint8_t _skip)
	{
		auto pair = _textureCache.find(pFile->Fullname());
		if (pair != _textureCache.end())
		{
			return pair->second;
		}

		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
		bgfx::TextureInfo* info;
		void* data = pFile->GetBuffer();

		if (nullptr != data)
		{
			bimg::ImageContainer* imageContainer = bimg::imageParse(getDefaultAllocator(), data, pFile->GetBufferLength());

			if (nullptr != imageContainer)
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
					handle = createTextureCube(
						static_cast<uint16_t>(imageContainer->m_width)
						, 1 < imageContainer->m_numMips
						, imageContainer->m_numLayers
						, static_cast<bgfx::TextureFormat::Enum>(imageContainer->m_format)
						, _flags
						, mem
					);
				}
				else if (1 < imageContainer->m_depth)
				{
					handle = createTexture3D(
						static_cast<uint16_t>(imageContainer->m_width)
						, static_cast<uint16_t>(imageContainer->m_height)
						, static_cast<uint16_t>(imageContainer->m_depth)
						, 1 < imageContainer->m_numMips
						, static_cast<bgfx::TextureFormat::Enum>(imageContainer->m_format)
						, _flags
						, mem
					);
				}
				else if (isTextureValid(0, false, imageContainer->m_numLayers, static_cast<bgfx::TextureFormat::Enum>(imageContainer->m_format), _flags))
				{
					handle = createTexture2D(
						static_cast<uint16_t>(imageContainer->m_width)
						, static_cast<uint16_t>(imageContainer->m_height)
						, 1 < imageContainer->m_numMips
						, imageContainer->m_numLayers
						, static_cast<bgfx::TextureFormat::Enum>(imageContainer->m_format)
						, _flags
						, mem
					);
				}

				if (isValid(handle))
				{
					setName(handle, pFile->Fullname().c_str());
				}

				info = ::new bgfx::TextureInfo();

				calcTextureSize(
					*info
					, static_cast<uint16_t>(imageContainer->m_width)
					, static_cast<uint16_t>(imageContainer->m_height)
					, static_cast<uint16_t>(imageContainer->m_depth)
					, imageContainer->m_cubeMap
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, static_cast<bgfx::TextureFormat::Enum>(imageContainer->m_format)
				);
			}
		}

		auto* texture = new Texture(handle, info);
		_textureCache.insert(std::make_pair(pFile->Fullname(), texture));
		return texture;
	}

	Texture* Texture::createTexture(const unsigned int width_, const unsigned int height_, const bgfx::TextureFormat::Enum format_,
		const bgfx::Memory* pData_, const unsigned long flags_, bgfx::TextureInfo* info_)
	{
		bgfx::TextureHandle handle = createTexture2D(static_cast<uint16_t>(width_), static_cast<uint16_t>(height_), true, 1,
			format_, static_cast<uint32_t>(flags_), pData_);

		if (nullptr != info_)
		{
			calcTextureSize(*info_
				, static_cast<uint16_t>(width_)
				, static_cast<uint16_t>(height_)
				, 0
				, false
				, true
				, 1
				, format_
			);
		}

		return new Texture(handle, info_);
	}

	Texture::Texture(bgfx::TextureHandle handle_, bgfx::TextureInfo* pInfo_ /*= nullptr*/) :
		m_pTextureInfo(pInfo_), m_Handle(handle_)
	{
	}

	Texture::~Texture()
	{
		destroy(m_Handle);
	}

	bgfx::TextureInfo* Texture::TextureInfo() const
	{
		return m_pTextureInfo;
	}

	bgfx::TextureHandle Texture::Handle() const
	{
		return m_Handle;
	}
}