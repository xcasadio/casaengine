#include <cstdint>

#include <bgfx/bgfx.h>

#include "Graphics/Renderer/Renderer.h"

#include <bgfx/platform.h>
#include <bx/bx.h>

#include "Maths/Matrix4.h"

#include "EngineSettings.h"
#include "Graphics/Vertices/VertexType.h"

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

	void IRenderer::Initialize(EngineSettings& settings, void* Hwnd)
	{
		bgfx::PlatformData pd;
		bx::memSet(&pd, 0, sizeof pd);
		pd.nwh = Hwnd;
		setPlatformData(pd);

		window_width = settings.WindowWidth;
		window_height = settings.WindowHeight;

		bgfx::Init init;
		init.type = settings.RendererType;
		init.vendorId = BGFX_PCI_ID_NONE;
		init.resolution.width = window_width;
		init.resolution.height = window_height;
		init.resolution.reset = BGFX_RESET_VSYNC;
		bgfx::init(init);

		//Setup(m_pWindow_); // desktop
		//Setup(); // mobile

		//bgfx::reset(settings_.WindowWidth, settings_.WindowHeight, BGFX_RESET_NONE);
		m_debugFlag = BGFX_DEBUG_TEXT;
		SetDebugFlag();

		SetClearColor(0
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL
			, Color::CornflowerBlue
			, 1.0f
			, 0);

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

	void IRenderer::BeginDraw()
	{
		//TODO : set by the current camera
		bgfx::setViewRect(0, 0, 0, window_width, window_height);
		bgfx::touch(0);
	}

	void IRenderer::EndDraw()
	{
		bgfx::frame();
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

	void IRenderer::SetClearColor(unsigned char index_, unsigned short flags, Color val, float depth, unsigned char stencil) const
	{
		bgfx::setViewClear(index_, flags, val.ToRGBA(), depth, stencil);
	}

	void IRenderer::Resize(unsigned int width_, unsigned height_)
	{
		//TODO
	}
}
