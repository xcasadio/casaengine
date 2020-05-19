#include <string>
#include <bgfx/bgfx.h>

#include "Graphics/Renderer/Renderer.h"

#include "Maths/Matrix4.h"
#include "Log/Logger.h"
#include "Exceptions.h"
#include "Log/LogManager.h"
#include "Parsers/Ini/INIReader.h"

#include "Resources/ResourceManager.h"
#include "Resources/MediaManager.h"
#include "StringUtils.h"
#include <stdint.h>
#include "bx/string.h"
#include "EngineSettings.h"

namespace CasaEngine
{
	IRenderer::IRenderer() :
		m_bDeviceLost(false)
	{
	}

	void IRenderer::shutdown()
	{
		bgfx::shutdown();
	}

	void IRenderer::Initialize(EngineSettings& settings_)
	{
		bgfx::Init init;
		init.type = settings_.RendererType;
		init.vendorId = BGFX_PCI_ID_NONE;
		init.resolution.width = settings_.WindowWidth;
		init.resolution.height = settings_.WindowHeight;
		init.resolution.reset = BGFX_RESET_VSYNC;
		bgfx::init(init);

		//Setup(m_pWindow_); // desktop
		//Setup(); // mobile

		//bgfx::reset(settings_.WindowWidth, settings_.WindowHeight, BGFX_RESET_NONE);
		m_debugFlag = BGFX_DEBUG_TEXT;
		SetDebugFlag();
		
		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL
			, CColor::CornflowerBlue.ToRGBA()
			, 0.0f
			, 0
		);

		VertexPositionColor::init();
		VertexPositionTexture::init();
		VertexPositionColorTexture::init();
		VertexPositionNormalTexture::init();
		VertexPositionColorNormalTexture::init();
	}

	bool IRenderer::IsDeviceLost() const
	{
		return m_bDeviceLost;
	}
	void IRenderer::SetDeviceLost()
	{
		m_bDeviceLost = true;
	}

	void IRenderer::SetWireframe(bool enable)
	{
		if (enable)
		{
			m_debugFlag |= BGFX_DEBUG_WIREFRAME;
		}
		else
		{
			m_debugFlag &= ~BGFX_DEBUG_WIREFRAME;
		}

		SetDebugFlag();
	}

	void IRenderer::SetDebugFlag()
	{
		bgfx::setDebug(m_debugFlag);
	}

#if CA_PLATFORM_MOBILE
	void IRenderer::Setup()
	{
		
	}
#else
	void IRenderer::Setup(sf::Window* pWindow_)
	{
		
	}
#endif

	void IRenderer::SetClearColor(unsigned char index_, CColor val) const
	{
		bgfx::setViewClear(index_, (uint32_t)val.ToRGBA());
	}

	void IRenderer::Resize(unsigned int width_, unsigned height_)
	{
		//TODO
	}

}
