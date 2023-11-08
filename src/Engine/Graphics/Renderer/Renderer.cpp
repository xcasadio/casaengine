#include <cstdint>

#include <bgfx/bgfx.h>

#include  "Graphics/Renderer/Renderer.hpp"

#include <bgfx/platform.h>
#include <bx/bx.h>

#include  "Maths/Matrix4.hpp"

#include  "EngineSettings.hpp"
#include  "Graphics/Vertices/VertexType.hpp"

namespace CasaEngine
{
	IRenderer::IRenderer() :
		_isDeviceLost(false)
	{
	}

	void IRenderer::shutdown()
	{
		bgfx::shutdown();
	}

	void IRenderer::Initialize(const EngineSettings& settings, void* hwnd)
	{
		bgfx::PlatformData pd;
		bx::memSet(&pd, 0, sizeof pd);
		pd.nwh = hwnd;
		setPlatformData(pd);

		_windowWidth = settings.WindowWidth;
		_windowHeight = settings.WindowHeight;

		bgfx::Init init;
		init.type = settings.RendererType;
		init.vendorId = BGFX_PCI_ID_NONE;
		init.resolution.width = _windowWidth;
		init.resolution.height = _windowHeight;
		init.resolution.reset = BGFX_RESET_VSYNC;
		bgfx::init(init);

		//Setup(m_pWindow_); // desktop
		//Setup(); // mobile

		//bgfx::reset(settings_.WindowWidth, settings_.WindowHeight, BGFX_RESET_NONE);
		_debugFlag = BGFX_DEBUG_TEXT;
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
		return _isDeviceLost;
	}

	void IRenderer::SetDeviceLost()
	{
		_isDeviceLost = true;
	}

	void IRenderer::SetWireFrame(const bool enable)
	{
		if (enable)
		{
			_debugFlag |= BGFX_DEBUG_WIREFRAME;
		}
		else
		{
			_debugFlag &= ~BGFX_DEBUG_WIREFRAME;
		}

		SetDebugFlag();
	}

	void IRenderer::BeginDraw()
	{
		//Test if the window is resized
		//bgfx::reset(settings_.WindowWidth, settings_.WindowHeight, BGFX_RESET_NONE);

		//TODO : set by the current camera
		bgfx::setViewRect(0, 0, 0, _windowWidth, _windowHeight);
		bgfx::touch(0);
	}

	void IRenderer::EndDraw()
	{
		bgfx::frame();
	}

	void IRenderer::SetDebugFlag()
	{
		bgfx::setDebug(_debugFlag);
	}

#if CA_PLATFORM_MOBILE
	void IRenderer::Setup()
	{
	}
#else
	void IRenderer::Setup(sf::Window* window)
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
