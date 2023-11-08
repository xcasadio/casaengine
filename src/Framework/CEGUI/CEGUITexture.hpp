
#ifndef _CEGUITEXTURE_H_
#define _CEGUITEXTURE_H_

#include "CA_Export.h"

#include "CEGUI/Texture.h"
#include "CEGUI/String.h"
#include "CEGUI/Vector.h"
#include "CEGUI/Size.h"
#include "Graphics/Textures/Texture.h"


namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT CEGUITexture : 
		public CEGUI::Texture
	{
	public:
		/**
		 * 
		 */
		CEGUITexture(const CEGUI::String& name_);

		/**
		 * 
		 */
		CEGUITexture(const CEGUI::String& name_, const CEGUI::String& filename, const CEGUI::String& resourceGroup);

		/**
		 * 
		 */
		CEGUITexture(const CEGUI::String& name_, const CEGUI::Sizef& size);

		/**
		 * 
		 */
		~CEGUITexture();

		/**
		 * 
		 */
		const CEGUI::String& getName() const;

		/**
		 * 
		 */
		const CEGUI::Sizef& getSize() const;

		/**
		 * 
		 */
		const CEGUI::Sizef& getOriginalDataSize() const;

		/**
		 * 
		 */
		const CEGUI::Vector2f& getTexelScaling() const;

		/**
		 * 
		 */
		void loadFromFile( const CEGUI::String& filename, const CEGUI::String& resourceGroup );

		/**
		 * 
		 */
		void loadFromMemory( const void* buffer, const CEGUI::Sizef& buffer_size, CEGUI::Texture::PixelFormat pixel_format );

		/**
		 * 
		 */
		void blitFromMemory( const void* sourceData, const CEGUI::Rectf& area );

		/**
		 * 
		 */
		void blitToMemory( void* targetData );

		/**
		 * 
		 */
		bool isPixelFormatSupported( const CEGUI::Texture::PixelFormat fmt ) const;

		/**
		 * 
		 */
		CasaEngine::Texture* GetTexture() const;

		/**
		 * 
		 */
		void SetTexture(CasaEngine::Texture* val);

	private:

		/**
		 * 
		 */
		void CreateTexture( const CEGUI::Sizef& size );

		/**
		 * 
		 */
		void ReleaseTexture();
		/**
		 * 
		 */
		void UpdateCachedScaleValues();


		//! cached pixel to texel mapping scale values.
		CEGUI::Vector2f m_TexelScaling;
		//! Size of the texture.
		CEGUI::Sizef m_Size;
		//! original pixel of size data loaded into texture
		CEGUI::Sizef m_DataSize;
		//! The name given for this texture.
		const CEGUI::String m_Name;
		//! 
		CasaEngine::Texture* m_pTexture;
	};

}  // namespace CasaEngine

#endif //_CEGUITEXTURE_H_
