
#include "Base.h"

#include "CEGUITextureTarget.h"


#include "Graphics/Renderer/Renderer.h"


namespace CasaEngine
{
	unsigned int CEGUITextureTarget::s_textureNumber = 0;

	/**
	 * 
	 */
	CEGUITextureTarget::CEGUITextureTarget(CasaEngine::TextureTarget *pRenderTarget_) :
		CEGUIRenderTarget<CEGUI::TextureTarget>(pRenderTarget_)
	{
		CA_TRACE("CEGUITextureTarget(%p) created\n", this);

		m_pTexture = ::new CEGUITexture("internal_ceguitexture_" + s_textureNumber++);
		declareRenderSize(CEGUI::Sizef(
			pRenderTarget_->GetTexture()->GetTexture()->GetSize().x,
			pRenderTarget_->GetTexture()->GetTexture()->GetSize().y));
	}

	/**
	 * 
	 */
	void CEGUITextureTarget::clear()
	{
		CColor clearColor = IRenderer::Get().GetClearColor();

		IRenderer::Get().SetClearColor(CColor::Transparent);
		m_pRenderTarget->Activate();
		IRenderer::Get().Clear(RenderParameter::Color);
		m_pRenderTarget->Deactivate();

		IRenderer::Get().SetClearColor(clearColor);
	}

	/**
	 * 
	 */
	CEGUI::Texture& CEGUITextureTarget::getTexture() const
	{
		CA_ASSERT(m_pTexture != nullptr, "CEGUITextureTarget::getTexture() : m_pTexture is nullptr");
		CasaEngine::TextureTarget *pTarget = dynamic_cast<CasaEngine::TextureTarget *>(m_pRenderTarget);
		m_pTexture->SetTexture(pTarget->GetTexture());
		return *m_pTexture;
	}

	/**
	 * 
	 */
	void CEGUITextureTarget::declareRenderSize(const CEGUI::Sizef& sz)
	{
		// exit if current size is enough
		if ((m_Area.getWidth() >= sz.d_width) 
			&& (m_Area.getHeight() >= sz.d_height))
		{
			return;
		}

		CA_TRACE("CEGUITextureTarget(%p) resize %f %f\n", this, sz.d_width, sz.d_height);

		setArea(CEGUI::Rectf(m_Area.getPosition(), sz));

		CasaEngine::TextureTarget* pTexTarget = dynamic_cast<CasaEngine::TextureTarget *>(m_pRenderTarget);
		pTexTarget->Create(
			Vector2I(m_Area.getSize().d_width, m_Area.getSize().d_height), 
			CasaEngine::PixelFormat::ARGB_8888);
		m_pTexture->SetTexture(pTexTarget->GetTexture());
	}

	/**
	 * 
	 */
	bool CEGUITextureTarget::isRenderingInverted() const
	{
		return m_pRenderTarget->IsRenderingInverted();
	}

} // namespace CasaEngine


#include "CEGUIRenderTarget.inl"
