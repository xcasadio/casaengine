#pragma once

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
		IRenderer(const IRenderer&) = delete;
		IRenderer& operator = (const IRenderer&) = delete;

		void Initialize(const EngineSettings& settings, void* hwnd);
		void shutdown();

		void Resize(unsigned int width_, unsigned height_);

		void SetClearColor(unsigned char index_, unsigned short flags, Color val, float depth = 1.0f, unsigned char stencil = 0) const;

		bool IsDeviceLost() const;
		void SetDeviceLost();

		void SetWireFrame(bool enable);
		void BeginDraw();
		void EndDraw();

	private:
		void SetDebugFlag();

#if CA_PLATFORM_MOBILE
		void Setup();
#else
		void Setup(sf::Window* window);
#endif

	private:
		bool _isDeviceLost;
		unsigned int _debugFlag;
		int _windowWidth;
		int _windowHeight;
	};
}
