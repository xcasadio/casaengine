
#include "Base.h"

#include "CEGUITexture.h"
#include "Graphics/Renderer/Enums.h"
#include "Maths/Vector2.h"
#include "Exceptions.h"
#include "Log/LogManager.h"



namespace CasaEngine
{
	/**
	 * 
	 */
	CEGUITexture::CEGUITexture(const CEGUI::String& name_) :
		m_Name(name_),
		m_pTexture(nullptr),
		m_TexelScaling(0, 0),
		m_DataSize(0, 0),
		m_Size(0, 0)
	{
		CA_TRACE("CEGUITexture(%p) created\n", this);
	}

	/**
	 * 
	 */
	CEGUITexture::CEGUITexture(const CEGUI::String& name_, const CEGUI::String& filename, const CEGUI::String& resourceGroup) :
		m_Name(name_),
		m_pTexture(nullptr),
		m_TexelScaling(0, 0),
		m_DataSize(0, 0),
		m_Size(0, 0)
	{
		CA_TRACE("CEGUITexture(%p) created\n", this);
		loadFromFile(filename, resourceGroup);
	}

	/**
	 * 
	 */
	CEGUITexture::CEGUITexture(const CEGUI::String& name_, const CEGUI::Sizef& size) :
		m_Name(name_),
		m_pTexture(nullptr),
		m_TexelScaling(0, 0),
		m_DataSize(0, 0),
		m_Size(0, 0)
	{
		CA_TRACE("CEGUITexture(%p) created\n", this);
		CreateTexture(size);
	}

	/**
	 * 
	 */
	CEGUITexture::~CEGUITexture()
	{
		ReleaseTexture();
	}

	/**
	 * 
	 */
	const CEGUI::String& CEGUITexture::getName() const
	{
		return m_Name;
	}

	/**
	 * 
	 */
	const CEGUI::Sizef& CEGUITexture::getSize() const
	{
		return m_Size;
	}

	/**
	 * 
	 */
	const CEGUI::Sizef& CEGUITexture::getOriginalDataSize() const
	{
		return m_DataSize;
	}

	/**
	 * 
	 */
	const CEGUI::Vector2f& CEGUITexture::getTexelScaling() const
	{
		return m_TexelScaling;
	}

	/**
	 * 
	 */
	void CEGUITexture::CreateTexture(const CEGUI::Sizef& size)
	{
		ReleaseTexture();
		m_pTexture = NEW_AO CasaEngine::Texture();

		m_pTexture->Create(Vector2I(size.d_width, size.d_height), CasaEngine::PixelFormat::ARGB_8888, 0, m_Name.c_str());
		m_DataSize.d_width = static_cast<float>(m_pTexture->GetTexture()->GetSize().x);
		m_DataSize.d_height = static_cast<float>(m_pTexture->GetTexture()->GetSize().y);
		m_Size = m_DataSize;
		UpdateCachedScaleValues();
	}

	/**
	 * 
	 */
	void CEGUITexture::ReleaseTexture()
	{
		CA_TRACE("CEGUITexture(%p) released\n", this);

		if (m_pTexture != nullptr)
		{
			DELETE_AO m_pTexture;
		}
	}

	/**
	 * 
	 */
	void CEGUITexture::loadFromFile(const CEGUI::String& filename, const CEGUI::String& resourceGroup)
	{
		ReleaseTexture();
		m_pTexture = NEW_AO CasaEngine::Texture();

		m_pTexture->CreateFromFile(filename.c_str(), CasaEngine::PixelFormat::ARGB_8888);
		m_DataSize.d_width = m_pTexture->GetTexture()->GetSize().x;
		m_DataSize.d_height = m_pTexture->GetTexture()->GetSize().y;
		m_Size = m_DataSize;
		UpdateCachedScaleValues();

		CA_TRACE("CEGUITexture(%p) load from file '%s' (size: %f %f | data size: %f %f | texel scaling %f %f)\n",
			this, filename.c_str(), m_Size.d_width, m_Size.d_height,
			m_DataSize.d_width, m_DataSize.d_height, m_TexelScaling.d_x, m_TexelScaling.d_y);
	}

	/**
	 * 
	 */
	void CEGUITexture::loadFromMemory(const void* buffer, const CEGUI::Sizef& buffer_size, CEGUI::Texture::PixelFormat pixel_format)
	{
		ReleaseTexture();
		m_pTexture = NEW_AO CasaEngine::Texture();

		CasaEngine::PixelFormat::TPixelFormat format;
		switch(pixel_format)
		{
		case PF_RGB:
			format = CasaEngine::PixelFormat::RGB_888;
			break;

		case PF_RGBA:
			format = CasaEngine::PixelFormat::ARGB_8888;
			break;

		case PF_RGBA_4444:
			format = CasaEngine::PixelFormat::ARGB_4444;
			break;

		case PF_RGB_565:
			format = CasaEngine::PixelFormat::RGB_888;
			break;

		case PF_PVRTC2:
			format = CasaEngine::PixelFormat::PVRTC2;
			break;

		case PF_PVRTC4:
			format = CasaEngine::PixelFormat::PVRTC4;
			break;

		case PF_RGB_DXT1:
			format = CasaEngine::PixelFormat::RGB_DXT1;
			break;

		case PF_RGBA_DXT1:
			format = CasaEngine::PixelFormat::RGBA_DXT1;
			break;

		case PF_RGBA_DXT3:
			format = CasaEngine::PixelFormat::RGBA_DXT3;
			break;

		case PF_RGBA_DXT5:
			format = CasaEngine::PixelFormat::RGBA_DXT5;
			break;
		};

		throw new std::exception("CEGUITexture::loadFromMemory() : not implemented with bgfx");

// 		CImage image(
// 			Vector2I(static_cast<int>(buffer_size.d_width), static_cast<int>(buffer_size.d_height) ), 
// 			format, 
// 			static_cast<const unsigned char*>(buffer));
// 		m_pTexture->CreateFromImage(image, format, 0, m_Name.c_str());
// 		m_DataSize.d_width = static_cast<float>(m_pTexture->GetTexture()->GetSize().x);
// 		m_DataSize.d_height = static_cast<float>(m_pTexture->GetTexture()->GetSize().y);
// 		m_Size = m_DataSize;
// 		UpdateCachedScaleValues();
// 
// 		CA_TRACE("CEGUITexture(%p) load from memory (size: %f %f | data size: %f %f | texel scaling %f %f)\n",
// 			this, m_Size.d_width, m_Size.d_height,
// 			m_DataSize.d_width, m_DataSize.d_height, m_TexelScaling.d_x, m_TexelScaling.d_y);
	}

	/**
	* Copy a RGBA buffer into the region of the texture
	 */
	void CEGUITexture::blitFromMemory(const void* sourceData, const CEGUI::Rectf& area)
	{
		throw CException("NotImplemented CEGUITexture::blitFromMemory()");
	}

	/**
	 * Copy all the pixel values into the buffer as RGBA values.
	 */
	void CEGUITexture::blitToMemory(void* targetData)
	{
		throw CException("NotImplemented CEGUITexture::blitFromMemory()");
	}

	/**
	 * 
	 */
	bool CEGUITexture::isPixelFormatSupported(const CEGUI::Texture::PixelFormat fmt) const
	{
		switch (fmt)
		{
		case PF_RGBA:
		case PF_RGB:
		case PF_RGBA_4444:
		case PF_RGB_565:
			return true;

		case PF_RGB_DXT1:
		case PF_RGBA_DXT1:
		case PF_RGBA_DXT3:
		case PF_RGBA_DXT5:
			return false; //d_owner.isS3TCSupported();

		default:
			return false;
		}
	}

	/**
	 * 
	 */
	void CEGUITexture::UpdateCachedScaleValues()
	{
		//
		// calculate what to use for x scale
		//
		const float orgW = m_DataSize.d_width;
		const float texW = m_Size.d_width;

		// if texture and original data width are the same, scale is based
		// on the original size.
		// if texture is wider (and source data was not stretched), scale
		// is based on the size of the resulting texture.
		m_TexelScaling.d_x = 1.0f / ((orgW == texW) ? orgW : texW);

		//
		// calculate what to use for y scale
		//
		const float orgH = m_DataSize.d_height;
		const float texH = m_Size.d_height;

		// if texture and original data height are the same, scale is based
		// on the original size.
		// if texture is taller (and source data was not stretched), scale
		// is based on the size of the resulting texture.
		m_TexelScaling.d_y = 1.0f / ((orgH == texH) ? orgH : texH);
	}

	/**
	 * 
	 */
	CasaEngine::Texture* CEGUITexture::GetTexture() const
	{
		return m_pTexture;
	}

	/**
	 * 
	 */
	void CEGUITexture::SetTexture(CasaEngine::Texture* val)
	{
		/*if (m_pTexture != nullptr)
		{
			DELETE_AO m_pTexture;
			m_pTexture = nullptr;
		}*/

		m_pTexture = val;

		m_DataSize.d_width = static_cast<float>(m_pTexture->GetTexture()->GetSize().x);
		m_DataSize.d_height = static_cast<float>(m_pTexture->GetTexture()->GetSize().y);
		m_Size = m_DataSize;
		UpdateCachedScaleValues();

		CA_TRACE("CEGUITexture(%p) set texture (size: %f %f | data size: %f %f | texel scaling %f %f)\n",
			this, m_Size.d_width, m_Size.d_height,
			m_DataSize.d_width, m_DataSize.d_height, m_TexelScaling.d_x, m_TexelScaling.d_y);
	}

} // namespace CasaEngine
