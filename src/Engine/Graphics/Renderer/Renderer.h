#ifndef RENDERER_H
#define RENDERER_H

#include "CA_Export.h"
#include "EngineSettings.h"
#include "Graphics/Color.h"
#include "SFML/Window/Window.hpp"

#define CA_DEFAULT_WIDTH 1280
#define CA_DEFAULT_HEIGHT 720

namespace CasaEngine
{
	class CA_EXPORT IRenderer
	{
	public:
		IRenderer();

		void Initialize(EngineSettings& settings, void* Hwnd);
		void shutdown();

		void Resize(unsigned int width_, unsigned height_);

		void SetClearColor(unsigned char index_, unsigned short flags, CColor val, float depth = 1.0f, unsigned char stencil = 0) const;

		bool IsDeviceLost() const;
		void SetDeviceLost();

		void SetWireframe(bool enable);
		void BeginDraw();
		void EndDraw();

	private:
		IRenderer(const IRenderer&) = delete;
		IRenderer& operator = (const IRenderer&) = delete;

		void SetDebugFlag();

#if CA_PLATFORM_MOBILE
		void Setup();
#else
		void Setup(sf::Window* pWindow_);
#endif

	private:
		bool m_bDeviceLost;
		unsigned int m_debugFlag;
		int window_width;
		int window_height;
	};
}

#endif
