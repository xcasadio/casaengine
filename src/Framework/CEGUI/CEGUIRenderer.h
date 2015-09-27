
#ifndef CEGUIRENDERER_H_
#define CEGUIRENDERER_H_

#include "CA_Export.h"
#include "Graphics/Renderer/Renderer.h"
#include "CEGUIViewportTarget.h"

#include "CEGUI/Renderer.h"
#include "CEGUI/ForwardRefs.h"
#include "CEGUI/String.h"
#include "CEGUI/TextureTarget.h"
#include "CEGUI/Size.h"
#include "CEGUI/Vector.h"
#include "CEGUIGeometryBuffer.h"
#include "CEGUITexture.h"
#include "CEGUITextureTarget.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT CEGUIRenderer : public CEGUI::Renderer
	{
	public:
		/**
		 * 
		 */
		CEGUIRenderer();

		/**
		 * 
		 */
		~CEGUIRenderer();

		/**
		 * 
		 */
		CEGUI::RenderTarget& getDefaultRenderTarget();
		
		/**
		 * 
		 */
		CEGUI::GeometryBuffer& createGeometryBuffer();
		
		/**
		 * 
		 */
		void destroyGeometryBuffer( const CEGUI::GeometryBuffer& buffer );
		
		/**
		 * 
		 */
		void destroyAllGeometryBuffers();
		
		/**
		 * 
		 */
		CEGUI::TextureTarget* createTextureTarget();
		
		/**
		 * 
		 */
		void destroyTextureTarget( CEGUI::TextureTarget* target );
		
		/**
		 * 
		 */
		void destroyAllTextureTargets();
		
		/**
		 * 
		 */
		CEGUI::Texture& createTexture( const CEGUI::String& name );
		
		/**
		 * 
		 */
		CEGUI::Texture& createTexture( const CEGUI::String& name, const CEGUI::String& filename, const CEGUI::String& resourceGroup );
		
		/**
		 * 
		 */
		CEGUI::Texture& createTexture( const CEGUI::String& name, const CEGUI::Sizef& size );
		
		/**
		 * 
		 */
		void destroyTexture( CEGUI::Texture& texture );
		
		/**
		 * 
		 */
		void destroyTexture( const CEGUI::String& name );
		
		/**
		 * 
		 */
		void destroyAllTextures();
		
		/**
		 * 
		 */
		CEGUI::Texture& getTexture( const CEGUI::String& name ) const;
		
		/**
		 * 
		 */
		bool isTextureDefined( const CEGUI::String& name ) const;
		
		/**
		 * 
		 */
		void beginRendering();
		
		/**
		 * 
		 */
		void endRendering();
		
		/**
		 * 
		 */
		void setDisplaySize( const CEGUI::Sizef& size );
		
		/**
		 * 
		 */
		const CEGUI::Sizef& getDisplaySize() const;
		
		/**
		 * 
		 */
		const CEGUI::Vector2f& getDisplayDPI() const;
		
		/**
		 * 
		 */
		CEGUI::uint getMaxTextureSize() const;
		
		/**
		 * 
		 */
		const CEGUI::String& getIdentifierString() const;

		/**
		 * 
		 */
		IEffect * Effect() const;

		/**
		 * 
		 */
		void SetBlendMode(const CEGUI::BlendMode mode, const bool force = false);

		/**
		 * 
		 */
		void SetViewProjMatrix(Matrix4 m_ViewProjMatrix);

		/**
		 * 
		 */
		Matrix4 GetViewProjMatrix() const;

	private:
		/**
		 * 
		 */
		void ThrowIfNameExists(const CEGUI::String& name) const;

		//! String holding the renderer identification text.
		static CEGUI::String m_IdentifierString;
		//! container type used to hold GeometryBuffers created.
		typedef std::vector<CEGUIGeometryBuffer*> GeometryBufferList;
		//! Container used to track geometry buffers.
		GeometryBufferList m_GeometryBuffers;
		//! container type used to hold TextureTargets we create.
		typedef std::vector<CEGUITextureTarget *> TextureTargetList;
		//! Container used to track texture targets.
		TextureTargetList m_TextureTargets;
		//! container type used to hold Textures we create.
		typedef std::map<CEGUI::String, CEGUITexture *, CEGUI::StringFastLessCompare
			CEGUI_MAP_ALLOC(CEGUI::String, CEGUITexture*)> TextureMap;
		//! Container used to track textures.
		TextureMap m_Textures;
		//! The default RenderTarget
		CEGUIViewportTarget *m_pDefaultTarget;
		//! What the renderer considers to be the current display size.
		CEGUI::Sizef m_DisplaySize;
		//! What the renderer considers to be the current display DPI resolution.
		CEGUI::Vector2f m_DisplayDPI;
		//! Effect used to render all elements.
		IEffect *m_pEffect;
		//!
		CEGUI::BlendMode m_ActiveBlendMode;
		//!
		Matrix4 m_ViewProjMatrix;
	};

} // namespace CasaEngine

#endif // CEGUIRENDERER_H_
