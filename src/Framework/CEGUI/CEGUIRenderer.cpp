
#include "Base.h"

#include "CEGUIRenderer.h"
#include "CEGUIGeometryBuffer.h"
#include "Graphics/ViewportTarget.h"
#include "Game/Game.h"
#include "CEGUIViewportTarget.h"
#include "CEGUITextureTarget.h"
#include "Exceptions.h"
#include "CEGUI/Logger.h"
#include "CEGUI/Exceptions.h"
#include "Memory/MemoryAllocation.h"

//

namespace CasaEngine
{

CEGUI::String CEGUIRenderer::m_IdentifierString("CasaEngine CEGUIRenderer");

/**
 * 
 */
CEGUIRenderer::CEGUIRenderer() :
	m_DisplayDPI(96.0f, 96.0f)
{
	ViewportTarget* pTarget = NEW_AO ViewportTarget();
	CRectangle rect;
	rect.End.x = Game::Instance()->GetWindow()->getSize().x;
	rect.End.y = Game::Instance()->GetWindow()->getSize().y;
	pTarget->SetArea(rect);
	
	m_pDefaultTarget = NEW_AO CEGUIViewportTarget(pTarget);
	m_DisplaySize.d_width = static_cast<float>(Game::Instance()->GetWindow()->getSize().x);
	m_DisplaySize.d_height = static_cast<float>(Game::Instance()->GetWindow()->getSize().y);

	//TODO : set in a LoadContent function
	m_pEffect = IRenderer::Get().CreateEffectFromFile("tex_color");
}

/**
 * 
 */
CEGUIRenderer::~CEGUIRenderer()
{
	if (nullptr != m_pEffect) DELETE_AO m_pEffect;
	if (nullptr != m_pDefaultTarget) DELETE_AO m_pDefaultTarget;

	destroyAllGeometryBuffers();
	destroyAllTextures();
	destroyAllTextureTargets();
}

/**
 * 
 */
CEGUI::RenderTarget& CEGUIRenderer::getDefaultRenderTarget()
{
	return *m_pDefaultTarget;
}

/**
 * 
 */
CEGUI::GeometryBuffer& CEGUIRenderer::createGeometryBuffer()
{
	CEGUIGeometryBuffer* b = ::new CEGUIGeometryBuffer();
	m_GeometryBuffers.push_back(b);
	return *b;
}

/**
 * 
 */
void CEGUIRenderer::destroyGeometryBuffer( const CEGUI::GeometryBuffer& buffer)
{
	GeometryBufferList::iterator i = std::find(m_GeometryBuffers.begin(),
		m_GeometryBuffers.end(),
		&buffer);

	if (m_GeometryBuffers.end() != i)
	{
		m_GeometryBuffers.erase(i);
		::delete &buffer;
	}
}

/**
 * 
 */
void CEGUIRenderer::destroyAllGeometryBuffers()
{
	while (!m_GeometryBuffers.empty())
		destroyGeometryBuffer(**m_GeometryBuffers.begin());
}

/**
 * 
 */
CEGUI::TextureTarget* CEGUIRenderer::createTextureTarget()
{
	CEGUITextureTarget* t = NEW_AO CEGUITextureTarget(
		IRenderer::Get().CreateTextureTarget(Vector2I(512, 512), PixelFormat::ARGB_8888));
	m_TextureTargets.push_back(t);
	return t;
}

/**
 * 
 */
void CEGUIRenderer::destroyTextureTarget(CEGUI::TextureTarget* target)
{
	TextureTargetList::iterator i = std::find(m_TextureTargets.begin(),
		m_TextureTargets.end(),
		target);

	if (m_TextureTargets.end() != i)
	{
		m_TextureTargets.erase(i);
		::delete target;
	}
}

/**
 * 
 */
void CEGUIRenderer::destroyAllTextureTargets()
{
 	while (!m_TextureTargets.empty())
	{
 		destroyTextureTarget(*m_TextureTargets.begin());
	}
}

/**
 * 
 */
CEGUI::Texture& CEGUIRenderer::createTexture( const CEGUI::String& name)
{
	ThrowIfNameExists(name);

	CEGUITexture* tex = ::new CEGUITexture(name);
	m_Textures[name] = tex;

	return *tex;
}

/**
 * 
 */
CEGUI::Texture& CEGUIRenderer::createTexture(const CEGUI::String& name, const CEGUI::String& filename, const CEGUI::String& resourceGroup)
{
	ThrowIfNameExists(name);

	CEGUITexture* tex = ::new CEGUITexture(name, filename, resourceGroup);
	m_Textures[name] = tex;

	return *tex;
}

/**
 * 
 */
CEGUI::Texture& CEGUIRenderer::createTexture(const CEGUI::String& name, const CEGUI::Sizef& size)
{
	ThrowIfNameExists(name);

	CEGUITexture* tex = ::new CEGUITexture(name, size);
	m_Textures[name] = tex;

	return *tex;
}

//----------------------------------------------------------------------------//
void CEGUIRenderer::ThrowIfNameExists(const CEGUI::String& name) const
{
	if (m_Textures.find(name) != m_Textures.end())
	{
		throw CEGUI::UnknownObjectException("[CasaEngine::CEGUIRenderer] Texture already exists: " + std::string(name.c_str()));
	}
}

/**
 * 
 */
void CEGUIRenderer::destroyTexture( CEGUI::Texture& texture)
{
	destroyTexture(texture.getName());
}

/**
 * 
 */
void CEGUIRenderer::destroyTexture(const CEGUI::String& name)
{
	TextureMap::iterator i = m_Textures.find(name);

	if (m_Textures.end() != i)
	{
		CEGUI::Logger* logger = CEGUI::Logger::getSingletonPtr();
		if (logger)
		{
			logger->logEvent("[CasaEngine::CEGUIRenderer] Destroyed texture: " + std::string(name.c_str()));
		}

		::delete i->second;
		m_Textures.erase(i);
	}
}

/**
 * 
 */
void CEGUIRenderer::destroyAllTextures()
{
 	while (!m_Textures.empty())
	{
 		destroyTexture(m_Textures.begin()->first);
	}
}

/**
 * 
 */
CEGUI::Texture& CEGUIRenderer::getTexture(const CEGUI::String& name) const
{
	TextureMap::const_iterator i = m_Textures.find(name);

	if (i == m_Textures.end())
	{
		throw CEGUI::UnknownObjectException("Texture does not exist: " + name);
	}

	return *i->second;
}

/**
 * 
 */
bool CEGUIRenderer::isTextureDefined(const CEGUI::String& name) const
{
	return m_Textures.find(name) != m_Textures.end();
}

/**
 * 
 */
void CEGUIRenderer::beginRendering()
{
	IRenderer::Get().Enable(RenderParameter::ScissorTest, true);
	IRenderer::Get().Enable(RenderParameter::ZEnable, false);
	//IRenderer::Get().Enable(RenderParameter::ZWrite, false);

	//IRenderer::Get().Enable(RenderParameter::AlphaTest, true);
	IRenderer::Get().Enable(RenderParameter::AlphaBlend, true);

	SetBlendMode(CEGUI::BM_NORMAL, true);

	//IRenderer::Get().Enable(RenderParameter::CullFace, RenderParameter::CULLFACE_NONE);

	//only one pass
	m_pEffect->Begin();
	std::vector<IEffectPass *>::iterator it = m_pEffect->PassesBeginIterator();
	(*it)->Begin();
}

/**
 * 
 */
void CEGUIRenderer::endRendering()
{
	//only one pass
	std::vector<IEffectPass *>::iterator it = m_pEffect->PassesBeginIterator();
	(*it)->End();
	m_pEffect->End();

	IRenderer::Get().Enable(RenderParameter::ScissorTest, false);
	IRenderer::Get().Enable(RenderParameter::ZEnable, true);
	//IRenderer::Get().Enable(RenderParameter::ZWrite, true);
	IRenderer::Get().Enable(RenderParameter::AlphaBlend, false);
	IRenderer::Get().Enable(RenderParameter::CullFace, RenderParameter::CULLFACE_CCW);
}

/**
 * 
 */
void CEGUIRenderer::SetBlendMode(const CEGUI::BlendMode mode, const bool force)
{
	return;

	// exit if mode is already set up (and update not forced)
	if ((m_ActiveBlendMode == mode) && !force)
		return;

	m_ActiveBlendMode = mode;

	if (m_ActiveBlendMode == CEGUI::BM_RTT_PREMULTIPLIED)
	{
		IRenderer::Get().SetupAlphaBlending(Blend::One, Blend::InvSrcAlpha);
	}
	else
	{
		IRenderer::Get().SetupAlphaBlending(Blend::SrcAlpha, Blend::InvSrcAlpha, Blend::InvDestAlpha, Blend::One);
	}
}

/**
 * 
 */
void CEGUIRenderer::setDisplaySize( const CEGUI::Sizef& size)
{
	if (size != m_DisplaySize)
	{
		m_DisplaySize = size;

		// FIXME: This is probably not the right thing to do in all cases.
		CEGUI::Rectf area(m_pDefaultTarget->getArea());
		area.setSize(size);
		m_pDefaultTarget->setArea(area);
	}
}

/**
 * 
 */
const CEGUI::Sizef& CEGUIRenderer::getDisplaySize() const
{
	return m_DisplaySize;
}

/**
 * 
 */
const CEGUI::Vector2f& CEGUIRenderer::getDisplayDPI() const
{
	return m_DisplayDPI;
}

/**
 * 
 */
CEGUI::uint CEGUIRenderer::getMaxTextureSize() const
{
	return ceguimin(IRenderer::Get().GetMaxTextureSize().x, IRenderer::Get().GetMaxTextureSize().y);
}

/**
 * 
 */
const CEGUI::String& CEGUIRenderer::getIdentifierString() const
{
	return m_IdentifierString;
}

/**
 * 
 */
IEffect* CEGUIRenderer::Effect() const
{
	return m_pEffect;
}

/**
 * 
 */
void CEGUIRenderer::SetViewProjMatrix(Matrix4 val_)
{
	m_ViewProjMatrix = val_;
}

/**
 * 
 */
Matrix4 CEGUIRenderer::GetViewProjMatrix() const
{
	return m_ViewProjMatrix;
}

} // namespace CasaEngine
